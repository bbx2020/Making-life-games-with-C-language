#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <graphics.h>
#include <conio.h>
#include <io.h>
#include<mmsystem.h>

#pragma comment(lib,"winmm.lib")




#define High_Max 100
#define Width_Max 100

int High = 48;
int Width = 64;
int Canvas[High_Max][Width_Max];
int Canvas1[High_Max][Width_Max];//捕猎者数组
int Canvas2[High_Max][Width_Max];//河流数组
int Canvas3[High_Max][Width_Max];//山地数组
int Breed_Num = 0;


void piantou(void) //开始界面
{
    // 设置随机函数种子
    srand((unsigned)time(NULL));

    // 初始化图形模式
    int  x, y;
    char c;
    settextcolor(WHITE);
    settextstyle(16, 8, _T("Courier"));	// 设置字体
    outtextxy(30, 484, _T("一切规律背后是否都隐藏着生命？"));
    Sleep(1000);
    settextcolor(GREEN);// 设置颜色
    setlinecolor(BLACK);

    for (int i = 0; i <= 479; i++)
    {
        outtextxy(30, 500, _T("按任意键继续......"));
        // 在随机位置显示三个随机字母
        for (int j = 0; j < 3; j++)
        {
            x = (rand() % 70) * 10;
            y = (rand() % 20) * 24;
            c = (rand() % 26) + 65;
            outtextxy(x, y, c);
        }

        // 画线擦掉一个像素行
        line(0, i, 699, i);

        Sleep(10);					// 延时
        if (i >= 479)	i = -1;		// 循环处理
        if (_kbhit())	break;		// 按任意键退出
    }

}
//片头结束
int menu(void)
{
    
    // 设置随机函数种子
    srand((unsigned)time(NULL));

    // 初始化图形模式
    int  x, y;
    char c;
    settextcolor(WHITE);
    settextstyle(16, 8, _T("Courier"));	// 设置字体
    outtextxy(30, 484, _T("随机世界"));
    outtextxy(140, 484, _T("射击场"));
    outtextxy(250, 484, _T("自定义世界"));
    outtextxy(400, 484, _T("上帝模式"));
    outtextxy(550, 484, _T("永恒"));
    settextcolor(RED);// 设置颜色
    setlinecolor(BLACK);
    MOUSEMSG m;
    m.uMsg = 0;
    m = GetMouseMsg();
    for (int i = 0; i <= 479; i++)
    {
        // 在随机位置显示三个随机字母
        for (int j = 0; j < 3; j++)
        {
            x = (rand() % 70) * 10;
            y = (rand() % 20) * 24;
            c = (rand() % 26) + 65;
            outtextxy(x, y, c);
        }

        // 画线擦掉一个像素行
        line(0, i, 699, i);
        line(0, i+1, 699, i+1);

        Sleep(10);					// 延时
        if (i >= 479)	i = -1;		// 循环处理
        MOUSEMSG m;
        m = GetMouseMsg();
       if (m.uMsg == WM_LBUTTONDOWN)
       {
           if (m.x >= 30 && m.x <= 100 && m.y >= 484 && m.y <= 492)
           {
               return 1;
               break;
           }
           if (m.x >= 140 && m.x <= 190 && m.y >= 484 && m.y <= 492)
           {
               return 2;
               break;
           }
           if (m.x >= 250 && m.x <= 350 && m.y >= 484 && m.y <= 492)
           {
               return 3;
               break;
           }
           if (m.x >= 400&& m.x <= 500 && m.y >= 484 && m.y <= 492)
           {
               return 4;
               break;
           }
           if (m.x >= 550 && m.x <= 650 && m.y >= 484 && m.y <= 492)
           {
               return 5;
               break;
           }
        }
            
    }


}

void gotoxy(int x, int y)//清屏
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle, pos);
}


void State_Init()//随机对数组赋值
{
    int i, j;
    srand(time(NULL));//初始化随机数 
    for (i = 0; i <= High; i++)
    {
        for (j = 0; j <= Width; j++)
        {
            Canvas[i][j] = rand() % 2;//随机赋值  
        }
    }
}

void river()//随机对数组赋值
{
    int i, j;
    srand(time(NULL));//初始化随机数 
    for (i = 15; i <= 30; i++)
    {
        for (j = (i-15)*4; j <= (i - 14) * 4; j++)
        {
            Canvas2[i][j] = 1;//随机赋值  
        }
    }
}

void mountain()//随机对数组赋值
{
    int i, j, w, m;
    srand(time(NULL));//初始化随机数 
    w = rand() % 48;
    m = rand() % 64;
    for (i = w; i <= w + 5; i++)
    {
        if (i == w)
            Canvas3[i][m] = 1;
        if (i == w + 1)
        {
            Canvas3[i][m - 1] = 1;
            Canvas3[i][m] = 1;
            Canvas3[i][m + 1] = 1;
        }
        if (i == w + 2)
        {
            Canvas3[i][m - 2] = 1;
            Canvas3[i][m - 1] = 1;
            Canvas3[i][m] = 1;
            Canvas3[i][m + 1] = 1;
            Canvas3[i][m + 2] = 1;
        }
        if (i == w + 3)
        {

            Canvas3[i][m - 1] = 1;
            Canvas3[i][m] = 1;
            Canvas3[i][m + 1] = 1;
        }
        if (i == w + 4)
        {
            Canvas3[i][m] = 1;
        }

    }
}
void hunter()//随机掠食者数组赋值
{
    int i, j;
    srand(time(NULL));//初始化随机数 
    for (i = 0; i <= High; i++)
    {
        for (j = 0; j <= Width; j++)
        {
            Canvas1[i][j] = rand() % 2;//随机赋值  
        }
    }
}




void Copy_arr(int tmp_map[][Width_Max], int map[][Width_Max])
{
    int i, j;
    for (i = 0; i < High; i++)
        for (j = 0; j < Width; j++)
            tmp_map[i][j] = map[i][j];
}

void Auto_Up()//自动更新 
{
    int NewCanvas[High_Max][Width_Max];//缓存 
    int RoundNum;//周围的个数 
    int i, j;
    Copy_arr(NewCanvas, Canvas);//先缓存 
    for (i = 0; i < High; i++)
    {
        for (j = 0; j < Width; j++)//比较缓存后的值在更新原本值 
        {
            RoundNum = NewCanvas[i - 1][j - 1] + NewCanvas[i - 1][j] + NewCanvas[i - 1][j + 1]
                + NewCanvas[i][j - 1] /*NewCanvas[i][j]*/ + NewCanvas[i][j + 1]
                + NewCanvas[i + 1][j - 1] + NewCanvas[i + 1][j] + NewCanvas[i + 1][j + 1];//将附近8个全部相加 
            if (RoundNum == 3)
                Canvas[i][j] = 1;
            else if (RoundNum == 2);//维持原状
            else
                Canvas[i][j] = 0;
        }
    }
    Breed_Num++;
}

void Auto_Up1()//自动更新 
{
    
    int NewCanvas1[High_Max][Width_Max];//缓存 
    int RoundNum;//周围的个数 
    int i, j;
    Copy_arr(NewCanvas1, Canvas1);//先缓存 
    for (i = 0; i < High; i++)
    {
        for (j = 0; j < Width; j++)//比较缓存后的值在更新原本值 
        {
            RoundNum = NewCanvas1[i - 1][j - 1] + NewCanvas1[i - 1][j] + NewCanvas1[i - 1][j + 1]
                + NewCanvas1[i][j - 1] /*NewCanvas[i][j]*/ + NewCanvas1[i][j + 1]
                + NewCanvas1[i + 1][j - 1] + NewCanvas1[i + 1][j] + NewCanvas1[i + 1][j + 1];//将附近8个全部相加 
            if (RoundNum == 3)
                Canvas1[i][j] = 1;
            else if (RoundNum == 2 );//维持原状
            else
                Canvas1[i][j] = 0;
        }
    }
    //Breed_Num++;
}


void chessboard()
{
    setlinecolor(WHITE);
    setfillcolor(WHITE);

    int i, j;
    for (i = 0; i <=High; i++)
    {
        line(0, 10 * i, 640, 10 * i);
    }
    for (j = 0; j <=Width; j++)
     {
       line(10*j, 0, 10 * j, 480); 
    }
    settextcolor(WHITE);
    settextstyle(16, 8, _T("Courier"));	// 设置字体
    outtextxy(650, 500, "返回");
}
void fill()
{
    int i, j;
    for (i = 0; i <High; i++)
    {
        for (j = 0; j < Width; j++)
        {
            if (Canvas[i][j] == 1)
            {
                setfillcolor(GREEN);
                floodfill(10 * j + 1, 10 * i + 1, WHITE, 0);
            }
            else
                setfillcolor(BLACK);
                floodfill(10 * j + 1, 10 * i + 1, WHITE, 0);
        }
    }
}

void showworld()
{
    int i, j;
    for (i = 0; i < High; i++)
    {
        for (j = 0; j < Width; j++)
        {
            if (Canvas2[i][j] == 1)
            {
            setfillcolor(BLUE);
            floodfill(10 * j + 1, 10 * i + 1, WHITE, 0);
            }
            else if (Canvas3[i][j] == 1)
            {
            setfillcolor(BROWN);
            floodfill(10 * j + 1, 10 * i + 1, WHITE, 0);
            }
            else if (Canvas1[i][j] == 1&&Canvas[i][j]==1)
            {
                setfillcolor(RED);
                floodfill(10 * j + 1, 10 * i + 1, WHITE, 0);
            }
            else if (Canvas1[i][j] == 0 && Canvas[i][j] == 1)
            {
                setfillcolor(GREEN);
                floodfill(10 * j + 1, 10 * i + 1, WHITE, 0);
            }
            else if (Canvas1[i][j] == 1 && Canvas[i][j] == 0)
            {
                setfillcolor(RED);
                floodfill(10 * j + 1, 10 * i + 1, WHITE, 0);
            }
            else if (Canvas2[i][j] == 1 )
            {
                setfillcolor(BLUE);
                floodfill(10 * j + 1, 10 * i + 1, WHITE, 0);
            }
            else if (Canvas3[i][j] == 1)
            {
                setfillcolor(BROWN);
                floodfill(10 * j + 1, 10 * i + 1, WHITE, 0);
            }
            else
            setfillcolor(BLACK);
            floodfill(10 * j + 1, 10 * i + 1, WHITE, 0);
        }
    }
}

   void Show()//生输出 ■ 死输出 □
    {
        fill();
    }
   
   /*int chose()
   {
       MOUSEMSG m;
       // 初始化绘图窗口
       cleardevice();
       m = GetMouseMsg();
       if (m.uMsg == WM_LBUTTONDOWN)
       {
           if (m.x >= 650 && m.x <= 672 && m.y >= 500 && m.y <= 508)
           {
               return 1;
           }
           else if (m.x >= 30 && m.x <= 94 && m.y >= 484 && m.y <= 492)
           {
               return 2;
           }
       }
   }
   */
void generation(int n)
{
    settextcolor(WHITE);
    settextstyle(16, 8, _T("Courier"));
    char num[20];
    sprintf(num, "%d", n);
    outtextxy(30, 560, _T("繁衍代数:"));
    outtextxy(100, 560,num);
}

void plane()  //射击场模式中本函数用来产生飞机
{
    int i=0;
    int w=5;
    srand(time(NULL));//初始化随机数 
    w =(rand()%45);
    for (i = w; i <= w+3; i++)
    {
        if (i == w)
        {
            Canvas[i][4] = 1;
            Canvas[i][5] = 1;
        }
        if (i == w+1)
        {
            Canvas[i][4] = 1;
            Canvas[i][5] = 1;
            Canvas[i][3] = 1;
            Canvas[i][6] = 1;
        }
        if (i == w+2)
        {
            Canvas[i][4] = 1;
            Canvas[i][7] = 1;
            Canvas[i][3] = 1;
            Canvas[i][6] = 1;
        }
        if (i == w+3)
        {
            Canvas[i][6] = 1;
            Canvas[i][5] = 1;
        }
    }
}

void zero()//使记录数组清零
{
    int i, j;
    for (i = 0; i <= High; i++)
    {
        for (j = 0; j <= Width; j++)
        {
            Canvas[i][j] = 0;
        }
    }
}

void zero1()//使记录数组清零
{
    int i, j;
    for (i = 0; i <= High; i++)
    {
        for (j = 0; j <= Width; j++)
        {
            Canvas1[i][j] = 0;
        }
    }
}

void zero2()//使记录数组清零
{
    int i, j;
    for (i = 0; i <= High; i++)
    {
        for (j = 0; j <= Width; j++)
        {
            Canvas2[i][j] = 0;
        }
    }
}

void zero3()//使记录数组清零
{
    int i, j;
    for (i = 0; i <= High; i++)
    {
        for (j = 0; j <= Width; j++)
        {
            Canvas3[i][j] = 0;
        }
    }
}

void fire()//本函数在射击场中控制拦截机发射
{
    int i, j;
    srand(time(NULL));//初始化随机数 
    for (i = 5; i <= 7; i++)
    {
        if (i == 5)
        {
            Canvas[i][60] = 1;
        }
        if (i == 6)
        {
            Canvas[i][60] = 1;
            Canvas[i][62] = 1;
        }
        if (i == 7)
        {
            Canvas[i][60] = 1;
            Canvas[i][61] = 1;
        }
    }
}



void note() //此函数用来记录鼠标点击的区域并及时显示显示在画布上
{
    chessboard();
    MOUSEMSG m;
    int n = 0;
    while (n==0)
    {
        m = GetMouseMsg();
        int i, j;
        switch (m.uMsg)
        {
        case WM_LBUTTONDOWN:
            i = m.x % 10;
            j = m.y % 10;
            // 如果点左键的同时按下了 Ctrl 键
            if (m.mkCtrl)
            {
                // 擦除方块
                setfillcolor(BLACK);
                floodfill(m.x, m.y, WHITE, 0);
                Canvas[j][i] = 0;
            }
            else
            {
                // 画一个小方块
                setfillcolor(GREEN);
                floodfill(m.x, m.y, WHITE, 0);
                Canvas[m.y/10][m.x/10] = 1;
            }
            break;

        case WM_RBUTTONUP:
            n = 1;
            break;// 按鼠标右键退出程序
        }
    }
    
}    

void yongheng()
  {
   /* while (1)
    {
        IMAGE eic;
        loadimage(&eic, _T("C:\\Users\\王桢华\\Desktop\\图片\\捕获25.png"));
        putimage(0, 0, &eic);
        generation(Breed_Num);
        Sleep(100);
        char input;
        if (_kbhit())
        {
            input = getch();
            if (input == ' ')
            {
                break;
            }
            
         }
     }
     */
    while (1)
    {
        cleardevice();
        Breed_Num++;
        
        settextcolor(WHITE);
        settextstyle(16, 8, _T("Courier"));
        outtextxy(300, 560, _T("电信学院万岁！"));
        generation(Breed_Num);
        IMAGE eic1;
        loadimage(&eic1, _T("C:\\Users\\王桢华\\Desktop\\图片\\捕获2222.PNG"));
        putimage(0, 0, &eic1);
        Sleep(100);
        IMAGE eic2;
        loadimage(&eic2, _T("C:\\Users\\王桢华\\Desktop\\图片\\捕获111.PNG"));
        putimage(0, 0, &eic2);
        Sleep(100);
        
    }
 }
  
 
    
int main()
{
   mciSendString(_T("open C:\\Users\\王桢华\\Music\\ouye.mp3 alias bkmusic"), NULL, NULL, NULL);//打开音乐文件
   mciSendString(_T("play bkmusic"), NULL, NULL, NULL);//播放音乐
   //mciSendString(_T("play C:\\Users\\王桢华\\Music\\ouye.mp3"), NULL, NULL, NULL);//播放音乐

   initgraph(700, 600);
   piantou();
   cleardevice();
   

// 以上是游戏开头
   while (1)
   {
       cleardevice();
       int i = menu();
       int n;
       switch (i)
       {
       case 1:
           //随机世界模式开始
           cleardevice();
           chessboard();
           State_Init();
           Show();
           while (1)
           {
               
               char input;
               if (_kbhit())
               {
                   input = getch();
                   if (input == ' ') 
                   {
                       break;
                   }
                   if (input == 'c')
                   {
                       zero();
                       Breed_Num = 0;
                   }
                   if (input == 'f')
                       State_Init();
               }
               Show();
               Auto_Up();
               Sleep(75);
               generation(Breed_Num);
           }
           //随机世界模式结束   
           break;
       case 2:
       {
           //射击场部分开始
           int count;//用于计数；
           cleardevice();
           outtextxy(30, 560, _T("按f键释放拦截机"));
           outtextxy(30, 540, _T("按c键清屏"));
           chessboard();
           zero();
           IMAGE ship;
           loadimage(&ship, _T("C:\\Users\\王桢华\\Desktop\\图片\\飞船.PNG"));
           putimage(645, 0, &ship);
           char input;
           for (count = 0; 1; count++)
           {
               if (count % 20 == 0)
               {
                   plane();
               }
               if (_kbhit())
               {
                   input = getch();
                   if (input == 'c')
                   {
                       zero();
                   }
                   if (input == 'f')
                       fire();
                   if (input == ' ')
                       break;
               }
               Show();
               Auto_Up();
               Sleep(10);
           }
           break;
       }
         //射击场部分结束
         //自定义模式开始
               case 3:
                n = 0;
               while (n == 0)
               {
                   cleardevice();
                   settextcolor(WHITE);
                   settextstyle(16, 8, _T("Courier"));	// 设置字体
                   outtextxy(650, 500, "返回");
                   zero();
                   note();
                   Auto_Up();
                   Show();
                   while (1)
                   {
                       Show();
                       Auto_Up();
                       Sleep(50);
                       generation(Breed_Num);
                       char input;
                       if (_kbhit())
                       {
                           input = getch();
                           if (input == 'c')
                           {
                               Breed_Num = 0;
                               break;
                           }
                           if (input == ' ')
                           {
                               n = 1;
                               Breed_Num = 0;
                               break;
                           }
                       }     
                   }
               }
               break;
               //自定义模式结束
               //上帝模式开始
              case 4:
                  cleardevice();
                  chessboard();
                  State_Init();
                  Show();
                  while (1)
                  {
                      //Show();
                      Auto_Up();
                      Sleep(125);
                      //generation(Breed_Num);
                      settextcolor(WHITE);
                      settextstyle(16, 8, _T("Courier"));	// 设置字体
                      outtextxy(40, 500, "按f释放掠食者");
                      outtextxy(40, 520, "按d释放绿细胞");
                      outtextxy(290, 540, "按r引入河流");
                      outtextxy(290, 520, "按m添加山地");
                      outtextxy(40, 540, "按c清理屏幕");

                      showworld();
                      Auto_Up1();
                      char input;
                      if (_kbhit())
                      {
                          input = getch();
                          if (input == ' ')
                          {
                              break;
                          }
                          if (input == 'f')
                          {
                              hunter();
                          }
                          if (input == 'c')
                          {
                              zero();
                              zero1();
                              zero2();
                              zero3();
                              Breed_Num = 0;
                          }

                          if (input == 'd')
                          {
                              State_Init();
                          }
                          if (input == 'r')
                          {
                             river();
                          }
                          if (input == 'm')
                          {
                              mountain();
                          }
                      }
                  }
                  break;    
              case 5:
              {
                  //永恒显示
                  cleardevice();
                  chessboard();
                  State_Init();
                  Show();          
                      while (1)
                      {
                          Show();
                          Auto_Up();
                          Sleep(100);
                          generation(Breed_Num);
                          char input;
                          if (_kbhit())
                          {
                              input = getch();
                              if (input == 'y')
                              {
                                  yongheng();
                                  break;
                              }
                          }
                      }
                  //随机世界模式结束   
                  break;
              }
          }
       }
      
    
    return 0;
}

