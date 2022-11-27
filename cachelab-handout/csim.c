#include "cachelab.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>

/*
学号：21302010042
姓名：侯斌洋
*/

int hit_count = 0;
int miss_count = 0;
int eviction_count = 0;
int All_time = 0;

//行
typedef struct line
{
    bool isValid;  //有效位
    int tag;       //标记位
    int last_time; //上次访问时间
} line;

//组
typedef line *set;

//缓存
typedef struct cache
{
    int lines_per_set; //每组的行数，即E
    int set_num;       //组数，即S
    int b;             //块偏移位数，即b
    int s;             //组索引位数，即s
    set *sets;         //存储结构
} cache;

//操作
typedef struct operation
{
    char opt;              //操作
    unsigned long address; //地址
    int size;              //大小
} operation;

//获得组索引
int get_set_index(unsigned long address, int s, int b)
{
    return (address >> b) % (1 << s);
}

//获得标记位
int get_tag(unsigned long address, int s, int b)
{
    return address >> (s + b);
}

//创建缓存，为sets申请空间
cache calloc_sets(int s, int E, int b)
{
    int set_num = (1 << s);
    set *sets = calloc(set_num, sizeof(set));
    for (int i = 0; i < set_num; i++)
    {
        sets[i] = calloc(E, sizeof(line));
    }
    cache result = {E, set_num, b, s, sets};
    return result;
}

//释放sets的空间
void free_sets(cache *c)
{
    for (int i = 0; i < c->set_num; i++)
    {
        free(c->sets[i]);
        c->sets[i] = NULL;
    }
    free(c->sets);
    c->sets = NULL;
}

//通过读取文件中的一行来获取一个操作并返回
operation get_opt(FILE *fp)
{
    char buf[100]; //缓冲区大小为100
    operation opt = {0, 0, 0};
    if (!fgets(buf, 100, fp)) //读取一行并将数据存在buf中
        return opt;
    sscanf(buf, " %c %lx,%d", &opt.opt, &opt.address, &opt.size); //用字符串给opt赋值
    return opt;
}

//获取命令行参数
void get_argvs(int argc, char **argvs, int *s, int *E, int *b, FILE **fp, bool *isDisplay)
{
    int opt;
    while ((opt = getopt(argc, argvs, "hvs:E:b:t:")) != -1)
    {
        switch (opt)
        {
        case 'h':
            printf("HELP\n");
            exit(0);
        case 'v':
            *isDisplay = true;
            break;
        case 's':
            *s = atoi(optarg);
            break;
        case 'E':
            *E = atoi(optarg);
            break;
        case 'b':
            *b = atoi(optarg);
            break;
        case 't':
            *fp = fopen(optarg, "r");
            if (*fp == NULL)
            {
                printf("Fail to open file\n");
                exit(-1);
            }
            break;
        default:
            break;
        }
    }
}

//进行load或store执行的操作，这里二者操作相同
void load_store(cache *cach, operation *opt, bool isDisplay, bool by_modify)
{
    if (isDisplay && !by_modify)
    {
        printf("%c %lx,%d ", opt->opt, opt->address, opt->size);
    }

    //获取组索引和标记
    int set_index = get_set_index(opt->address, cach->s, cach->b);
    int tag = get_tag(opt->address, cach->s, cach->b);
    line *right_line = NULL;

    //检验是否命中
    for (int i = 0; i < cach->lines_per_set; i++)
    {
        if (cach->sets[set_index][i].tag == tag && cach->sets[set_index][i].isValid)
        {
            right_line = &cach->sets[set_index][i];
        }
    }
    if (right_line) //若命中
    {
        hit_count++;
        if (isDisplay)
        {
            printf("hit ");
        }
    }
    else //若不命中
    {
        miss_count++;
        if (isDisplay)
        {
            printf("miss ");
        }
        //检验组中是否有空位
        for (int i = 0; i < cach->lines_per_set; i++)
        {
            if (!cach->sets[set_index][i].isValid)
            {
                right_line = &cach->sets[set_index][i];
                break;
            }
        }
        if (right_line) //若有空位
        {
            right_line->isValid = true;
        }
        else //若没有空位
        {
            eviction_count++;
            if (isDisplay)
            {
                printf("eviction ");
            }
            //寻找last_time最小即距离上一次访问时间最久的一行
            //执行驱逐
            right_line = &cach->sets[set_index][0];
            for (int i = 0; i < cach->lines_per_set; i++)
            {
                if (cach->sets[set_index][i].last_time < right_line->last_time)
                {
                    right_line = &cach->sets[set_index][i];
                }
            }
        }
        right_line->tag = tag; //更新标记
    }

    if (isDisplay && !by_modify)
    {
        printf("\n");
    }
    //更新时间
    right_line->last_time = All_time;
    All_time++;
}

//进行modify执行的操作，一次modify即一次load加上一次store
void modify(cache *cach, operation *opt, bool isDisplay)
{
    if (isDisplay)
    {
        printf("%c %lx,%d ", opt->opt, opt->address, opt->size);
    }

    //执行一次load
    opt->opt = 'L';
    load_store(cach, opt, isDisplay, true);
    //再执行一次store
    opt->opt = 'S';
    load_store(cach, opt, isDisplay, true);

    if (isDisplay)
    {
        printf("\n");
    }
}

int main(int argc, char **argvs)
{
    //变量初始化
    hit_count = 0;
    miss_count = 0;
    eviction_count = 0;
    FILE *fp = NULL;
    bool isDisplay = false;
    int s = 0, E = 0, b = 0;
    operation opt;

    //获取命令行参数
    get_argvs(argc, argvs, &s, &E, &b, &fp, &isDisplay);

    //根据读取的s，E，b创建缓存
    cache cach = calloc_sets(s, E, b);

    //处理操作
    while ((opt = get_opt(fp)).opt)
    {
        switch (opt.opt)
        {
        case 'I':
            continue;
        case 'M':
            modify(&cach, &opt, isDisplay);
            break;
        case 'S':
            load_store(&cach, &opt, isDisplay, false);
            break;
        case 'L':
            load_store(&cach, &opt, isDisplay, false);
            break;
        }
    }

    //进行收尾
    fclose(fp);
    free_sets(&cach);
    printSummary(hit_count, miss_count, eviction_count);
    return 0;
}
