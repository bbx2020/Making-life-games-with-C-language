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
int Canvas1[High_Max][Width_Max];//����������
int Canvas2[High_Max][Width_Max];//��������
int Canvas3[High_Max][Width_Max];//ɽ������
int Breed_Num = 0;


void piantou(void) //��ʼ����
{
    // ���������������
    srand((unsigned)time(NULL));

    // ��ʼ��ͼ��ģʽ
    int  x, y;
    char c;
    settextcolor(WHITE);
    settextstyle(16, 8, _T("Courier"));	// ��������
    outtextxy(30, 484, _T("һ�й��ɱ����Ƿ�������������"));
    Sleep(1000);
    settextcolor(GREEN);// ������ɫ
    setlinecolor(BLACK);

    for (int i = 0; i <= 479; i++)
    {
        outtextxy(30, 500, _T("�����������......"));
        // �����λ����ʾ���������ĸ
        for (int j = 0; j < 3; j++)
        {
            x = (rand() % 70) * 10;
            y = (rand() % 20) * 24;
            c = (rand() % 26) + 65;
            outtextxy(x, y, c);
        }

        // ���߲���һ��������
        line(0, i, 699, i);

        Sleep(10);					// ��ʱ
        if (i >= 479)	i = -1;		// ѭ������
        if (_kbhit())	break;		// ��������˳�
    }

}
//Ƭͷ����
int menu(void)
{
    
    // ���������������
    srand((unsigned)time(NULL));

    // ��ʼ��ͼ��ģʽ
    int  x, y;
    char c;
    settextcolor(WHITE);
    settextstyle(16, 8, _T("Courier"));	// ��������
    outtextxy(30, 484, _T("�������"));
    outtextxy(140, 484, _T("�����"));
    outtextxy(250, 484, _T("�Զ�������"));
    outtextxy(400, 484, _T("�ϵ�ģʽ"));
    outtextxy(550, 484, _T("����"));
    settextcolor(RED);// ������ɫ
    setlinecolor(BLACK);
    MOUSEMSG m;
    m.uMsg = 0;
    m = GetMouseMsg();
    for (int i = 0; i <= 479; i++)
    {
        // �����λ����ʾ���������ĸ
        for (int j = 0; j < 3; j++)
        {
            x = (rand() % 70) * 10;
            y = (rand() % 20) * 24;
            c = (rand() % 26) + 65;
            outtextxy(x, y, c);
        }

        // ���߲���һ��������
        line(0, i, 699, i);
        line(0, i+1, 699, i+1);

        Sleep(10);					// ��ʱ
        if (i >= 479)	i = -1;		// ѭ������
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

void gotoxy(int x, int y)//����
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(handle, pos);
}


void State_Init()//��������鸳ֵ
{
    int i, j;
    srand(time(NULL));//��ʼ������� 
    for (i = 0; i <= High; i++)
    {
        for (j = 0; j <= Width; j++)
        {
            Canvas[i][j] = rand() % 2;//�����ֵ  
        }
    }
}

void river()//��������鸳ֵ
{
    int i, j;
    srand(time(NULL));//��ʼ������� 
    for (i = 15; i <= 30; i++)
    {
        for (j = (i-15)*4; j <= (i - 14) * 4; j++)
        {
            Canvas2[i][j] = 1;//�����ֵ  
        }
    }
}

void mountain()//��������鸳ֵ
{
    int i, j, w, m;
    srand(time(NULL));//��ʼ������� 
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
void hunter()//�����ʳ�����鸳ֵ
{
    int i, j;
    srand(time(NULL));//��ʼ������� 
    for (i = 0; i <= High; i++)
    {
        for (j = 0; j <= Width; j++)
        {
            Canvas1[i][j] = rand() % 2;//�����ֵ  
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

void Auto_Up()//�Զ����� 
{
    int NewCanvas[High_Max][Width_Max];//���� 
    int RoundNum;//��Χ�ĸ��� 
    int i, j;
    Copy_arr(NewCanvas, Canvas);//�Ȼ��� 
    for (i = 0; i < High; i++)
    {
        for (j = 0; j < Width; j++)//�Ƚϻ�����ֵ�ڸ���ԭ��ֵ 
        {
            RoundNum = NewCanvas[i - 1][j - 1] + NewCanvas[i - 1][j] + NewCanvas[i - 1][j + 1]
                + NewCanvas[i][j - 1] /*NewCanvas[i][j]*/ + NewCanvas[i][j + 1]
                + NewCanvas[i + 1][j - 1] + NewCanvas[i + 1][j] + NewCanvas[i + 1][j + 1];//������8��ȫ����� 
            if (RoundNum == 3)
                Canvas[i][j] = 1;
            else if (RoundNum == 2);//ά��ԭ״
            else
                Canvas[i][j] = 0;
        }
    }
    Breed_Num++;
}

void Auto_Up1()//�Զ����� 
{
    
    int NewCanvas1[High_Max][Width_Max];//���� 
    int RoundNum;//��Χ�ĸ��� 
    int i, j;
    Copy_arr(NewCanvas1, Canvas1);//�Ȼ��� 
    for (i = 0; i < High; i++)
    {
        for (j = 0; j < Width; j++)//�Ƚϻ�����ֵ�ڸ���ԭ��ֵ 
        {
            RoundNum = NewCanvas1[i - 1][j - 1] + NewCanvas1[i - 1][j] + NewCanvas1[i - 1][j + 1]
                + NewCanvas1[i][j - 1] /*NewCanvas[i][j]*/ + NewCanvas1[i][j + 1]
                + NewCanvas1[i + 1][j - 1] + NewCanvas1[i + 1][j] + NewCanvas1[i + 1][j + 1];//������8��ȫ����� 
            if (RoundNum == 3)
                Canvas1[i][j] = 1;
            else if (RoundNum == 2 );//ά��ԭ״
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
    settextstyle(16, 8, _T("Courier"));	// ��������
    outtextxy(650, 500, "����");
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

   void Show()//����� �� ����� ��
    {
        fill();
    }
   
   /*int chose()
   {
       MOUSEMSG m;
       // ��ʼ����ͼ����
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
    outtextxy(30, 560, _T("���ܴ���:"));
    outtextxy(100, 560,num);
}

void plane()  //�����ģʽ�б��������������ɻ�
{
    int i=0;
    int w=5;
    srand(time(NULL));//��ʼ������� 
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

void zero()//ʹ��¼��������
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

void zero1()//ʹ��¼��������
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

void zero2()//ʹ��¼��������
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

void zero3()//ʹ��¼��������
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

void fire()//��������������п������ػ�����
{
    int i, j;
    srand(time(NULL));//��ʼ������� 
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



void note() //�˺���������¼����������򲢼�ʱ��ʾ��ʾ�ڻ�����
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
            // ����������ͬʱ������ Ctrl ��
            if (m.mkCtrl)
            {
                // ��������
                setfillcolor(BLACK);
                floodfill(m.x, m.y, WHITE, 0);
                Canvas[j][i] = 0;
            }
            else
            {
                // ��һ��С����
                setfillcolor(GREEN);
                floodfill(m.x, m.y, WHITE, 0);
                Canvas[m.y/10][m.x/10] = 1;
            }
            break;

        case WM_RBUTTONUP:
            n = 1;
            break;// ������Ҽ��˳�����
        }
    }
    
}    

void yongheng()
  {
   /* while (1)
    {
        IMAGE eic;
        loadimage(&eic, _T("C:\\Users\\���廪\\Desktop\\ͼƬ\\����25.png"));
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
        outtextxy(300, 560, _T("����ѧԺ���꣡"));
        generation(Breed_Num);
        IMAGE eic1;
        loadimage(&eic1, _T("C:\\Users\\���廪\\Desktop\\ͼƬ\\����2222.PNG"));
        putimage(0, 0, &eic1);
        Sleep(100);
        IMAGE eic2;
        loadimage(&eic2, _T("C:\\Users\\���廪\\Desktop\\ͼƬ\\����111.PNG"));
        putimage(0, 0, &eic2);
        Sleep(100);
        
    }
 }
  
 
    
int main()
{
   mciSendString(_T("open C:\\Users\\���廪\\Music\\ouye.mp3 alias bkmusic"), NULL, NULL, NULL);//�������ļ�
   mciSendString(_T("play bkmusic"), NULL, NULL, NULL);//��������
   //mciSendString(_T("play C:\\Users\\���廪\\Music\\ouye.mp3"), NULL, NULL, NULL);//��������

   initgraph(700, 600);
   piantou();
   cleardevice();
   

// ��������Ϸ��ͷ
   while (1)
   {
       cleardevice();
       int i = menu();
       int n;
       switch (i)
       {
       case 1:
           //�������ģʽ��ʼ
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
           //�������ģʽ����   
           break;
       case 2:
       {
           //��������ֿ�ʼ
           int count;//���ڼ�����
           cleardevice();
           outtextxy(30, 560, _T("��f���ͷ����ػ�"));
           outtextxy(30, 540, _T("��c������"));
           chessboard();
           zero();
           IMAGE ship;
           loadimage(&ship, _T("C:\\Users\\���廪\\Desktop\\ͼƬ\\�ɴ�.PNG"));
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
         //��������ֽ���
         //�Զ���ģʽ��ʼ
               case 3:
                n = 0;
               while (n == 0)
               {
                   cleardevice();
                   settextcolor(WHITE);
                   settextstyle(16, 8, _T("Courier"));	// ��������
                   outtextxy(650, 500, "����");
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
               //�Զ���ģʽ����
               //�ϵ�ģʽ��ʼ
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
                      settextstyle(16, 8, _T("Courier"));	// ��������
                      outtextxy(40, 500, "��f�ͷ���ʳ��");
                      outtextxy(40, 520, "��d�ͷ���ϸ��");
                      outtextxy(290, 540, "��r�������");
                      outtextxy(290, 520, "��m���ɽ��");
                      outtextxy(40, 540, "��c������Ļ");

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
                  //������ʾ
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
                  //�������ģʽ����   
                  break;
              }
          }
       }
      
    
    return 0;
}

