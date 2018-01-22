#include <stdafx.h>

/****************************
    Graphical Toolbox 1.0
	 Created By:
       Charles Watkins
  November 10, 1995 2:45 am
****************************/
#include	<Stdlib.H>
#include	<String.H>
#include	<Malloc.H>
#include	<Conio.H>
#include	<Ctype.H>
#include	<Stdio.H>
#include	<Math.H>
#include	<Time.h>
#include	<Dos.H>
//#include	<Dir.H>
//#include	<Mem.H>

#define	YES	101
#define	NO	102

#define	OFF	103
#define	ON	104

#define	NORMAL		107
#define	FORM		108
#define	PASTE		109
#define	MEDUIM		110
#define	SMALL		111
#define	SINK		113
#define	STRETCH		114
#define	SMALLBLEND	115

/*******Pen*Modes*********/
#define DRAW             0
#define BRUSH            1
#define X_BRUSH          2
#define PAINT            3
#define INVERT           4
#define DITHER           5
#define BLEND            6
#define ERASE            7
#define SMEAR            8
#define XMAP             9
#define YMAP            10
#define XCOLOR          11
#define YCOLOR          12
#define FFADE           13
#define BRIGHTEN        14
#define DARKEN          15
#define ADD             16
#define SUBTRACT        17
/*******Tile Modes*******/
#define T_FILL             0
#define T_X_BLEND          1
#define T_PAINT            2
#define T_ERASE            3
#define T_INVERT           4
#define T_DITHER           5
#define T_BLEND            6
#define T_SMEAR            7
#define T_XMAP             8
#define T_YMAP             9
#define T_XCOLOR          10
#define T_YCOLOR          11
#define T_FFADE           12
#define T_BRIGHTEN        13
#define T_DARKEN          14
#define T_ADD             15
#define T_SUBTRACT        16

#define	ENTER	28
#define	TAB	15
#define	INS     82
#define	DEL	83
#define	RIGHT	96
#define	LEFT	97
#define	UP	98
#define	DOWN	99
#define SHIFT	54
#define CTRL	29
#define ALT	56
#define	SPACE	57
#define	F1	59
#define	F2	60
#define	F3	61
#define	F4	62
#define	F5	63
#define	F6	64
#define	F7	65
#define	F8	66
#define	F9	67
#define	F10	68
#define	F11	87
#define	F12	88
#define PGUP	93
#define PGDN	94


char *styles[]={"DRAW",
                "BRUSH",
                "X-BRUSH",
                "PAINT",
                "INVERT",
                "DITHER",
                "BLEND",
                "ERASE",
                "SMEAR",
                "XMAP",
                "YMAP",
                "XCOLOR",
                "YCOLOR",
                "FFADE",
                "BRIGHTEN",
                "DARKEN",
                "ADD",
                "SUBTRACT"};

char *tstyles[]={"FILL",
                 "X-BLEND",
                 "PAINT",
                 "ERASE",
                 "INVERT",
                 "DITHER",
                 "BLEND",
                 "SMEAR",
                 "XMAP",
                 "YMAP",
                 "XCOLOR",
                 "YCOLOR",
                 "FFADE",
                 "BRIGHTEN",
                 "DARKEN",
                 "ADD",
                 "SUBTRACT"};

extern unsigned _stklen=+10000;



void          *csr,*lib,*data,*clip,*scn,*menu,*scrap;
int           X,Y,BUTTON,mouse=OFF,drawmouse=YES;
char          Pal[768],Key[200];
unsigned      key=0,Extended=OFF;
float         Cos[360],Sin[360];
float         cx=0,cy=0,cz=0;
unsigned char color1=0,color2=31;
int           file_open=NO;
char          filename[14];
int           size=5,Obj=0;
int           osize=3,oObj=1;
char          pen[81],pentype=0,o_pen=1;
int           Draw_Mode=0,Tile_Mode=0,TILE=OFF;
int           Ds=0,Ts=0;
int           WRAP=ON;

void Setup(void);
void interrupt (*Old_Key_Isr)(...);
void interrupt   New_Key_Int (...);
void Set_VGA_Palette(void);
void Make_Pal(int,int,int,int,int,int,int,int);
void Set_All_Palette(void);
void Close(void);
void Exit(char *);
void Calulate(void);
void Beep(void);
void Fade_Out(void);
void Fade_In(void);
void Smear_Out(void);
int  Mouse_Check(void);
void Reset_Mouse(void);
void Put_Mouse(int,int);
void Mouse_Status(void);
void Draw_Mouse(void);
void Text_Small(int,int,char *,int,void *);
void Text(int,int,char *,int,void *);
void Text_Big(int,int,char *,int,void *);
void Line(int,int,int,int,int,void *);
void Box(int,int,int,int,void *,int,char *,int);
void Spin(int,int,int,int,int,int);
void Spin2(float,float,float,int,int,int);
void Prompt(char *);
void Menu(void);
void Credits(void);
void Load(void);
void Save(void);
void New(void);
void Editing(void);
void Draw_Object(void);
void Quad(void);
void Time(void);
void Set_Pen(int);
void Draw_Pen(int,int,int,void *);
void Pen_Draw(int,int);
void Pen_Brush(int,int);
void Pen_Paint(int,int);
void Pen_Invert(int,int);
void Pen_Dither(int,int);
void Pen_Blend(int,int);
void Pen_Smear(int,int);
void Pen_Xmap(int,int);
void Pen_Ymap(int,int);
void Pen_Xcolor(int,int);
void Pen_Ycolor(int,int);
void Pen_Ffade(int,int);
void Pen_X_Brush(int,int);
void Pen_Brighten(int,int);
void Pen_Darken(int,int);
void Pen_Add(int,int);
void Pen_Sub(int,int);
void Pen_Erase(int,int);
void Tile_XBlend(int,int);
void Mapping(void);


int _tmain(int argc, _TCHAR* argv[])
{
 Setup();
 Menu();        /*from which all is controled*/
 Close();
}


void Setup(void)
{
 int i;
 textmode(C80);
 textcolor(LIGHTGRAY);
 textbackground(BLACK);
 clrscr();
 _setcursortype(_SOLIDCURSOR);
 gotoxy(1,1);
 textcolor(WHITE);
 textbackground(RED);
 cprintf("                             Graphical ToolBox V.1.00                           ");
 textbackground(BLACK);
 cprintf("   Setting Palette...\n\r");

 cprintf("   Initilizing Mouse...\n\r");
 mouse=OFF;
 if(Mouse_Check()==1) mouse=ON;
 if(mouse==ON) Reset_Mouse(); else Exit("Activate Mouse...");
 cprintf("   Allocating Memory...\n\r");
 if((csr   =malloc(0x800 ))==NULL) Exit("Memory 1x allocation failed...");
 if((lib   =malloc(0xFC00))==NULL) Exit("Memory 2x allocation failed...");
 if((data  =malloc(0xFC00))==NULL) Exit("Memory 3x allocation failed...");
 if((scn   =malloc(0xFA00))==NULL) Exit("Memory 4x allocation failed...");
 if((menu  =malloc(0xFA00))==NULL) Exit("Memory 5x allocation failed...");
 if((scrap =malloc(0xFA00))==NULL) Exit("Memory 6x allocation failed...");
 if((clip  =malloc(0x6C00))==NULL) Exit("Memory 7x allocation failed...");
 memset(clip  ,64,0x6C00);
 memset(csr   , 0,0x800);
 memset(lib   , 0,0xFC00);
 memset(data  , 0,0xFC00);
 memset(scn   , 0,0xFA00);
 memset(menu  , 0,0xFA00);
 memset(scrap , 0,0xFA00);
 cprintf("   Preparing Video State...\n\r");
 cprintf("                         [                       ]\n\r");
 for(i=0;i<23;i++) { delay(random(20)); gotoxy(27+i,6); cprintf("."); }

 Calulate();
 cprintf("\n\r   Loading Graphics...\n\r");
 FILE *file;
 file=fopen("C:\\GT\\GTS.LIB","rb");
 fread(lib,0xFC00,1,file);
 fclose(file);
 file=fopen("C:\\GT\\TEXT7.LIB","rb");
 fread(data,0xFC00,1,file);
 fclose(file);
 movedata(FP_SEG(data),FP_OFF(data),FP_SEG(lib),FP_OFF(lib)+15*1024,27648);
 file=fopen("C:\\GT\\CURSOR.IMG","rb");
 fread(csr,0x400,1,file);
 fclose(file);
 cprintf("                         [                ]\n\r");
 for(i=0;i<17;i++) { delay(random(50)); gotoxy(27+i,8); cprintf("."); }
 asm { mov ax,0x0013; int 0x10 }
 Set_All_Palette();
 for(i=0;i<200;i++) Key[i]=OFF;
 Old_Key_Isr=getvect(0x09);
 setvect(0x09,New_Key_Int);
}

void interrupt   New_Key_Int (...)
{
_asm { sti
       in al,0x60
       xor ah,ah
       mov key,ax
       in al,0x61
       or al,0x82
       out 0x61,al
       and al,0x7F
       out 0x61,al
       mov al,0x20
       out 0x20,al     };

if(Extended==ON)
 {
  if(key==82 ) Key[82]=ON;  //INS
  if(key==83 ) Key[83]=ON;  //DEL
  if(key==77 ) Key[RIGHT]=ON;  //RIGHT
  if(key==75 ) Key[LEFT ]=ON;  //LEFT
  if(key==72 ) Key[UP   ]=ON;  //UP
  if(key==80 ) Key[DOWN ]=ON;  //DOWN
  if(key==73 ) Key[93]=ON;  //PGUP
  if(key==81 ) Key[94]=ON;  //PGDN
  if(key==56 ) Key[56]=ON;  //RIGHT ALT
  if(key==29 ) Key[29]=ON;  //RIGHT CTRL
  if(key==184) Key[56]=OFF; //RIGHT ALT
  if(key==157) Key[29]=OFF; //RIGHT CTRL
  if(key==156) Key[28]=ON;  //RIGHT ENTER
  if(key==53 ) Key[53]=ON;  //DIVIDE
  if(key==77+128) Key[RIGHT]=OFF;
  if(key==75+128) Key[LEFT ]=OFF;
  if(key==72+128) Key[UP   ]=OFF;
  if(key==80+128) Key[DOWN ]=OFF;
  if(key!=224) { Extended=OFF; key=0; }
 }


  if(key==224) Extended=ON;
  if(key<=88 ) Key[key]=ON;
  if(key>=128) Key[key-128]=OFF;
}

void Set_VGA_Palette(void)
{
 union REGS r;
 struct SREGS sr;
 r.x.ax=0x1012;
 r.x.bx=0;
 r.x.cx=256;
 r.x.dx=FP_OFF(Pal);
 sr.es =FP_SEG(Pal);
 int86x(0x10,&r,&r,&sr);
}

void Set_All_Palette(void)
{
 Make_Pal(32*0   ,32*1   ,0 ,0 ,0 ,0 ,64,0 ); /* Green    */
 Make_Pal(32*1   ,32*2   ,0 ,0 ,0 ,0 ,0 ,64); /* Blue     */
 Make_Pal(32*2   ,32*3   ,0 ,0 ,0 ,64,0 ,0 ); /* Red      */
 Make_Pal(32*3   ,32*4   ,0 ,0 ,0 ,64,64,64); /* Gray     */
 Make_Pal(32*4   ,32*5   ,0 ,0 ,0 ,64,64,0 ); /* Gold     */
 Make_Pal(32*5   ,32*6   ,0 ,0 ,0 ,64,0 ,64); /* Purple   */
 Make_Pal(32*6   ,32*6+7 ,0 ,0 ,0 ,13,5 ,0 ); /* Brown ป */
 Make_Pal(32*6+7 ,32*7   ,13,5 ,0 ,64,56,49); /* Brown ผ */
 Make_Pal(32*7   ,32*8   ,0 ,0 ,0 ,32,32,64); /* Cyan     */
 Set_VGA_Palette();
}

void Make_Pal(int a,int b,int r1,int g1,int b1,int r2,int g2,int b2)
{
 int e,f,g,p,i;
 for(i=a;i<b;i++)
 {
  p=((i-a)*100)/(b-a);
  e=((r2-r1)*p)/100;
  f=((g2-g1)*p)/100;
  g=((b2-b1)*p)/100;
  Pal[i*3+0]=r1+e;
  Pal[i*3+1]=g1+f;
  Pal[i*3+2]=b1+g;
 }
}

void Close(void)
{
 setvect(0x09,Old_Key_Isr);
 textcolor(LIGHTGRAY);
 textbackground(BLACK);
 textmode(3);
 clrscr();
 _setcursortype(_NORMALCURSOR);
 textcolor(WHITE); textbackground(BLUE);
 gotoxy(2,1); cprintf("ษอออออออ[ADDRESS]ออออออออป");
 gotoxy(2,2); cprintf("บ                        บ");
 gotoxy(2,3); cprintf("บ                        บ");
 gotoxy(2,4); cprintf("บ                        บ");
 gotoxy(2,5); cprintf("บ                        บ");
 gotoxy(2,6); cprintf("ศออออออออออออออออออออออออผ");
 textcolor(LIGHTGREEN); textbackground(BLUE);
 gotoxy(3,2); cprintf("*Creator of GT          ");
 gotoxy(3,3); cprintf(" Charles Watkins        ");
 gotoxy(3,4); cprintf(" PO Box 1978            ");
 gotoxy(3,5); cprintf(" Stone Mountain GA,30083");
 textcolor(LIGHTGRAY); textbackground(BLACK);
 gotoxy(2,6); cprintf("\n\r");
 cprintf("\n\r\n\r\n\rThank You...\n\r\n\r");
 memset(csr   ,0,0x800);
 memset(lib   ,0,0xFC00);
 memset(data  ,0,0xFC00);
 memset(clip  ,0,0x6C00);
 memset(scn   ,0,0xFA00);
 memset(menu  ,0,0xFA00);
 memset(scrap ,0,0xFA00);
}

void Exit(char *txt)
{
textmode(C80);
cprintf("\n\r\n\r    Terminal Execution error: \n\r        %s\n\r",txt);
exit(0);
}

void Calulate(void)
{
 int i;
 for(i=0;i<360;i++)
 {
  Cos[i]=cos(i*.017453);
  Sin[i]=sin(i*.017453);
 }
 Beep();
}

void Beep(void)
{
sound(1600); delay(10);
sound(1327); delay(10);
sound(1600); delay(10);
sound(7);    delay(10);
nosound();
}

void Fade_Out(void)
{
 int i,a,step=5;
 char Pal2[768];
 for(i=0;i<768;i++) Pal2[i]=Pal[i];

 for(i=100;i>0-step;i-=step) {
			for(a=0;a<768;a++) Pal[a]=(Pal2[a]*i)/100;
			Set_VGA_Palette();
		       }
 for(i=0;i<768;i++) Pal[i]=Pal2[i];
}

void Fade_In(void)
{
 int i,a,step=5;
 char Pal2[768];
 for(i=0;i<768;i++) Pal2[i]=Pal[i];
 for(i=0;i<100+step;i+=step) {
			 for(a=0;a<768;a++) Pal[a]=(Pal2[a]*i)/100;
			 Set_VGA_Palette();
			}
 for(i=0;i<768;i++) Pal[i]=Pal2[i];
}

void Smear_Out(void)
{
 int i,fuz[200],a;
 for(i=0;i<200;i++) fuz[i]=random(10)+10;
 movedata(FP_SEG(scn),FP_OFF(scn),FP_SEG(scrap),FP_OFF(scrap),0xFA00);
 for(a=0;a<33;a++)
 {
  for(i=0;i<200;i+=2)
  {
   if(fuz[i]*a<320)
    movedata(FP_SEG(scrap),FP_OFF(scrap)+i*320+fuz[i]*a,
             FP_SEG(scn  ),FP_OFF(scn  )+i*320,320-fuz[i]*a);
   if(fuz[i+1]*a<320)
    movedata(FP_SEG(scrap),FP_OFF(scrap)+i*320+320,
             FP_SEG(scn  ),FP_OFF(scn  )+i*320+320+fuz[i+1]*a,320-fuz[i+1]*a);
  }
  movedata(FP_SEG(scn),FP_OFF(scn),0xA000,0x00,0xFA00);
  memset(scn,36,0xFA00);
 }
}

int  Mouse_Check(void)
{
 union REGS mousreg;
 mousreg.x.ax=0;
 mousreg.x.bx=0;
 mousreg.x.cx=0;
 mousreg.x.dx=0;
 int86(0x33,&mousreg,&mousreg);
 if(mousreg.x.ax==0) return 0;
 else return 1;
}

void Reset_Mouse(void)
{
 union REGS r;
 r.x.ax = 0;
 int86(0x33,&r,&r);
 int86(0x33,&r,&r);
}

void Put_Mouse(int x,int y)
{
 union REGS r;
 r.x.ax=4;
 r.x.cx=x*2;
 r.x.dx=y;
 int86(0x33,&r,&r);
}

void Mouse_Status(void)
{
 static l=0,r=0,u=0,d=0,s=0;
 int a,b;
 a=X,b=Y;
 union REGS c;
 c.x.ax=3;
 int86(0x33,&c,&c);
 BUTTON=_BX;
 Y=_DX;
 X=_CX/2;
 if((Key[ALT ]==ON) && (Key[SHIFT]==OFF)) X=a;
 if((Key[CTRL]==ON) && (Key[SHIFT]==OFF)) Y=b;
 if((Key[SHIFT]==OFF) && ((Key[ALT]==ON) || (Key[CTRL]==ON)))
     Put_Mouse(X,Y);
 if((Key[SPACE]==ON) && (s!=ON)) BUTTON=1;
 if((Key[LEFT ]==ON) && (l!=ON)) { X-=size; if(X<0) X=0;     Put_Mouse(X,Y); }
 if((Key[RIGHT]==ON) && (r!=ON)) { X+=size; if(X>319) X=319; Put_Mouse(X,Y); }
 if((Key[UP   ]==ON) && (u!=ON)) { Y-=size; if(Y<0)  Y=0;    Put_Mouse(X,Y); }
 if((Key[DOWN ]==ON) && (d!=ON)) { Y+=size; if(Y>198) Y=198; Put_Mouse(X,Y); }
 l=Key[LEFT],r=Key[RIGHT];
 u=Key[UP]  ,d=Key[DOWN];
 s=Key[SPACE];
}

void Draw_Mouse(void)
{
  if(drawmouse==YES)
  {
   int a[16]={ 2,3,4,5,6,7,8,9,10,11,12,13,13,6,4,2 },b;
   for(b=0;b<16;b++) { if(a[b]+X>319) a[b]=319-X; if(a[b]<0) a[b]=0; }
   for(b=0;b<16;b++)   if(Y+b>199) a[b]=0;
   for(b=0;b<16;b++)
    if(a[b]!=0) movedata(FP_SEG(scn),FP_OFF(scn)+X+(Y+b)*320,
                         FP_SEG(csr),FP_OFF(csr)+(20+b)*32+6,a[b]);
   for(b=0;b<16;b++)
    if(a[b]!=0) movedata(FP_SEG(csr),FP_OFF(csr)+(4+b)*32+6,
		         FP_SEG(scn),FP_OFF(scn)+X+(Y+b)*320,a[b]);
   movedata(FP_SEG(scn),FP_OFF(scn),0xA000,0x00,0xFA00);

   for(b=0;b<16;b++)
    if(a[b]!=0) movedata(FP_SEG(csr),FP_OFF(csr)+(20+b)*32+6,
                         FP_SEG(scn),FP_OFF(scn)+X+(Y+b)*320,a[b]);
  }
 else
 movedata(FP_SEG(scn),FP_OFF(scn),0xA000,0x00,0xFA00);

}

void Text_Small(int x,int y,char *txt,int t,void *buf)
{
 int a,b,c,d,e,g;
 unsigned f,h,i,j,k,l;
 for(a=0;a<strlen(txt);a++)
 {
  g=-1;
  if((txt[a]>='a') && (txt[a]<='z')) g=txt[a]-'a';
  if((txt[a]>='A') && (txt[a]<='Z')) g=txt[a]-'A';
  if((txt[a]>='1') && (txt[a]<='9')) g=txt[a]-'1'+30;
  if(txt[a]=='0') g=39;
  if(txt[a]==':') g=40;
  if(txt[a]=='\\') g=41;
  if(txt[a]=='=') g=26;
  if(txt[a]=='-') g=27;
  if(txt[a]=='+') g=28;
  if(txt[a]=='.') g=29;
  if(g==-1) continue;
  e=g/5;
  d=g-e*5;
  for(c=0;c<7;c++)
  for(b=0;b<5;b++)
  {
   f=peekb(FP_SEG(lib),FP_OFF(lib)+b+c*32+d*6+e*8*32);
   if(f!=0)
   {
    if(t==BLEND)
    {
     h=peekb(FP_SEG(buf),FP_OFF(buf)+c*320+b+a*6+x+y*320);
     i=h/32; j=h-(i*32);
     k=f/32; l=f-(k*32);
     f=(l+j)/2+i*32;
    }
    if(t==SINK)
    {
     h=peekb(FP_SEG(buf),FP_OFF(buf)+c*320+b+a*6+x+y*320);
     i=h/32;
     k=f/32; l=f-(k*32);
     f=l+i*32;
    }
    if(t==NORMAL);
    pokeb(FP_SEG(buf),FP_OFF(buf)+c*320+b+a*6+x+y*320,f);
   }
  }
 }
}

void Text(int x,int y,char *txt,int t,void *buf)
{
 int a=0,b=0,c,d=0,e=0,f=0,g,h,k,l,m,n,o;

 for(b=0;b<strlen(txt);b++)
 {
  e=77;
  if((txt[b]>='A') && (txt[b]<='Z')) e=txt[b]-'A';
  if((txt[b]>='a') && (txt[b]<='z')) e=txt[b]-'a';
  if((txt[b]>='0') && (txt[b]<='9')) e=txt[b]-'0'+36;
  if(txt[b]=='.') e=26;
  if(txt[b]=='-') e=27;
  if(txt[b]=='&') e=28;
  if(txt[b]=='(') e=29;
  if(txt[b]=='!') e=30;
  if(txt[b]=='#') e=31;
  if(txt[b]=='*') e=32;
  if(txt[b]=='$') e=33;
  if(txt[b]=='@') e=34;
  if(txt[b]=='^') e=35;
  if(txt[b]=='+') e=46;
  c=e/2;
  if(c*2==e) d=0; else d=16;
  if(e!=77)
  if(t!=PASTE)
  for(g=0;g<12;g++)
  for(a=0;a<13;a++)
  {
   n=(unsigned char)peekb(FP_SEG(lib),FP_OFF(lib)+3*1024+c*512+d+a*32+g);
   if(n==36) continue;
   o=(unsigned char)peekb(FP_SEG(buf),FP_OFF(buf)+a*320+x+y*320+f+g);
   l=o/32; k=o-l*32;
   l=n/32; h=n-l*32;
   if(t==UP     ) { m=k+h;      l=o/32; }
   if(t==DOWN   ) { m=k-h;      l=o/32; }
   if(t==BLEND  ) { m=(h-20)+k; l=n/32; }
   if(t==NORMAL ) { m=h;        l=n/32; }
   if(t==STRETCH) { m=h;        l=3;    }
   if(m>31) m=31; if(m<0) m=0;
   if(t!=STRETCH)
   pokeb(FP_SEG(buf),FP_OFF(buf)+a*320+x+y*320+f+g,m+l*32);
   else
   {
    pokeb(FP_SEG(buf),FP_OFF(buf)+a*640+x+y*320+f+g,m+1*32);
    pokeb(FP_SEG(buf),FP_OFF(buf)+a*640+x+y*320+320+f+g,m+6*32);
   }
  }
  if(e!=77)
  if(t==PASTE)
  for(a=0;a<13;a++)
   movedata(FP_SEG(lib),FP_OFF(lib)+3*1024+c*512+d+a*32,
            FP_SEG(buf),FP_OFF(buf)+a*320+x+y*320+f,12);
  f+=12;
 }
}

void Text_Big(int x,int y,char *txt,int t,void *buf)
{
 int a=0,b=0,e=0,f=0,g,h;

 for(b=0;b<strlen(txt);b++)
 {
  e=77;
  if(txt[b]==' ') f-=15;
  if((txt[b]>='A') && (txt[b]<='Z')) e=txt[b]-'A';
  if((txt[b]>='a') && (txt[b]<='z')) e=txt[b]-'a';
  if(e!=77)
  for(g=0;g<20;g++)
  for(a=0;a<24;a++)
  {

   h=(unsigned)peekb(FP_SEG(lib),FP_OFF(lib)+15*1024+e*1024+a*32+g);
   if(h!=36)
    if(t==DOWN)
    pokeb(FP_SEG(buf),FP_OFF(buf)+a*320+x+y*320+f*320+g,h);
    else
    pokeb(FP_SEG(buf),FP_OFF(buf)+a*320+x+y*320+f+g,h);
  }
  f+=20; if(t==DOWN) f+=5;
 }
}

void Line(int x1,int y1,int x2,int y2,int c,void *buf)
{
 int dx,dy,error=0,xinc=1,yinc=1,x,y,i;

 x=x1,y=y1;
 dx=x2-x1;
 dy=y2-y1;

 if(dx<0) { xinc=-1; dx=-dx; }
 if(dy<0) { yinc=-1; dy=-dy; }

 if(dx>dy)
  for(i=0;i<=dx;i++)
   {
   if((x>0) && (x<319) && (y>0) && (y<199))
   pokeb(FP_SEG(buf),FP_OFF(buf)+x+y*320,c);
   error+=dy;
   if(error>dx) { error-=dx; y+=yinc; }
   x+=xinc;
   }
 else
  for(i=0;i<=dy;i++)
  {
   if((x>0) && (x<319) && (y>0) && (y<199))
   pokeb(FP_SEG(buf),FP_OFF(buf)+x+y*320,c);
   error+=dx;
   if(error>0) { error-=dy; x+=xinc; }
   y+=yinc;
  }
}

void Box(int x1,int y1,int x2,int y2,void *buf,int t,char *txt,int mode)
{
 int a,b,c,e,i;

 for(e=0;e<10;e++)
 for(i=0;i<7;i++)
 for(c=0;c<32;c++)
 if((c+i*32<=y2) && (c+i*32>=y1))
 {
  a=(x2-x1)-e*32;
  if(a>32) a=32;
  if(a<0) a=0;
  movedata(FP_SEG(lib  ),FP_OFF(lib  )+1024*t+c*32,
           FP_SEG(scrap),FP_OFF(scrap)+x1+e*32+(c+i*32)*320,a);
 }

  //Top Line
  for(b=x1+1;b<x2-1;b++)
   pokeb(FP_SEG(scrap),FP_OFF(scrap)+b+y1*320+320,32*4-1);
  //Bottom Line
  for(b=x1+1;b<x2-1;b++)
   pokeb(FP_SEG(scrap),FP_OFF(scrap)+b+y2*320-640,32*4-10);
  //Left Line
  for(b=y1+2;b<y2-1;b++)
   pokeb(FP_SEG(scrap),FP_OFF(scrap)+x1+1+b*320,32*4-1);
  //Right Line
  for(b=y1+2;b<y2-1;b++)
   pokeb(FP_SEG(scrap),FP_OFF(scrap)+x2-2+b*320,32*4-10);



 if(mode==FORM)
   Text((x1+x2)/2-strlen(txt)*6,y1+(y2-y1)/2-6,txt,PASTE,scrap);

 if(mode==MEDUIM)
  if(t==46)
   Text((x1+x2)/2-strlen(txt)*6,y1+(y2-y1)/2-6,txt,DOWN,scrap);
  else
   Text((x1+x2)/2-strlen(txt)*6,y1+(y2-y1)/2-6,txt,BLEND,scrap);

 if(mode==UP)
   Text((x1+x2)/2-strlen(txt)*6,y1+(y2-y1)/2-6,txt,UP,scrap);

 if(mode==DOWN)
   Text((x1+x2)/2-strlen(txt)*6,y1+(y2-y1)/2-6,txt,DOWN,scrap);

 if(mode==NORMAL)
   Text((x1+x2)/2-strlen(txt)*6,y1+(y2-y1)/2-6,txt,NORMAL,scrap);

 if(mode==BLEND)
   Text((x1+x2)/2-strlen(txt)*6,y1+(y2-y1)/2-6,txt,BLEND,scrap);

 if(mode==SMALL)
   Text_Small((x1+x2)/2-strlen(txt)*3,y1+(y2-y1)/2-3,txt,NORMAL,scrap);

 if(mode==SMALLBLEND)
   Text_Small((x1+x2)/2-strlen(txt)*3,y1+(y2-y1)/2-3,txt,BLEND,scrap);



  for(b=y1;b<y2;b++)
  movedata(FP_SEG(scrap),FP_OFF(scrap)+x1+b*320,
           FP_SEG(buf   ),FP_OFF(buf   )+x1+b*320,x2-x1);

}

void Spin(int x,int y,int z,int sx,int sy,int sz)
{
 float x1,y1,z1;
 float x2,y2,z2;

 x1=x *Cos[sz]+y *Sin[sz]; //Z
 y1=y *Cos[sz]-x *Sin[sz];
 x2=x1*Cos[sy]-z *Sin[sy]; //Y
 z1=x1*Sin[sy]+z *Cos[sy];
 y2=y1*Cos[sx]+z1*Sin[sx]; //X
 z2=z1*Cos[sx]-y1*Sin[sx];

 cx=int(x2);
 cy=int(y2);
 cz=int(z2);
}

void Spin2(float x,float y,float z,int sx,int sy,int sz)
{
 float x1,y1,z1;
 float x2,y2,z2;

 x1=x *Cos[sz]+y *Sin[sz]; //Z
 y1=y *Cos[sz]-x *Sin[sz];
 x2=x1*Cos[sy]-z *Sin[sy]; //Y
 z1=x1*Sin[sy]+z *Cos[sy];
 y2=y1*Cos[sx]+z1*Sin[sx]; //X
 z2=z1*Cos[sx]-y1*Sin[sx];

 cx=x2;
 cy=y2;
 cz=z2;
}

void Prompt(char *txt)
{
 int a,b=0,c=0,i=0,fiz[32],exit=NO;
 a=strlen(txt)*7;
 movedata(FP_SEG(scn),FP_OFF(scn),FP_SEG(scrap),FP_OFF(scrap),0xFA00);
 Box(160-a/2,80,160+a/2,120,scn,48,txt,SMALL);
 Box(160-a/2,80,160+a/2,120,scrap,46,txt,SMALL);
 for(c=0;c<32;c++) fiz[c]=random(64);
 fiz[0]=0;

 for(i=0;i<32;i++) Make_Pal(32*1,32*2,0,0,0,i*2,i*2,i*2);

 while(exit!=YES)
 {
  Mouse_Status();
  if((X>160-a/2) && (X<160+a/2) && (Y>80) && (Y<120) && (BUTTON==0) && (b==1))
  { exit=YES; Beep(); }
  if((BUTTON==0) && (b==1))
  { b=0; Box(160-a/2,80,160+a/2,120,scn,48,txt,SMALL); }
  if(((X<160-a/2) || (X>160+a/2) || (Y<80) || (Y>120)) && (b==1))
  { b=0; Box(160-a/2,80,160+a/2,120,scn,48,txt,SMALL); }
  if((X>160-a/2) && (X<160+a/2) && (Y>80) && (Y<120) && (BUTTON==1) &&
      (b!=1))
  { b=1;  Box(160-a/2,80,160+a/2,120,scn,46,txt,SMALL); }
  c=fiz[1];
  for(i=2;i<32;i++) fiz[i-1]=fiz[i];
  fiz[31]=c;
  for(i=0;i<32;i++)
  {
   Pal[i*3]=fiz[i];
   Pal[i*3+1]=fiz[i];
   Pal[i*3+2]=fiz[i];
  }
  Set_VGA_Palette();
  Draw_Mouse();
 }
 Set_All_Palette();
 movedata(FP_SEG(scrap),FP_OFF(scrap),FP_SEG(scn),FP_OFF(scn),0xFA00);
}

void Menu(void)
{
 int star[3][90],points[90][2],fiz[37],a,b,c,d=0,e,i,bb=7,item=0,exit=NO;
 int sx,sy,sz,tile=5;
 int oX,oY,change=1;
 float floatx,floaty;
 randomize();
 sx=0,sy=0,sz=0;
 for(b=0;b<5 ;b++)
 for(a=0;a<18;a++)
 {
  sz=a*20;
  if(sz>359) sz-=360;
  if(b==0) Spin( 8,0,-16,sx,sy,sz);
  if(b==1) Spin(15,0,- 8,sx,sy,sz);
  if(b==2) Spin(18,0,  0,sx,sy,sz);
  if(b==3) Spin(15,0,  8,sx,sy,sz);
  if(b==4) Spin( 8,0, 16,sx,sy,sz);
  star[0][a+b*18]=cx,star[1][a+b*18]=cy,star[2][a+b*18]=cz;
 }
 sx=0,sy=0,sz=0;
 for(i=0;i<36;i++)
 {
  sz+=10;
  if(sz>359) sz-=360;
  Spin(10,0,0,sx,sy,sz);
  fiz[i]=cx;
 }

 sx=45,sy=45,sz=45;


 while(exit!=YES)
 {
  if(change==1)
  {
   Box(0,0,319,199,menu,50,""                  ,SMALL);
   Box(80,60+0*18,240,75+0*18,menu,46,"NEW"    ,MEDUIM);
   Box(80,60+1*18,240,75+1*18,menu,46,"LOAD"   ,MEDUIM);
   Box(80,60+2*18,240,75+2*18,menu,46,"SAVE"   ,MEDUIM);
   Box(80,60+3*18,240,75+3*18,menu,46,"EDITING",MEDUIM);
   Box(80,60+4*18,240,75+4*18,menu,46,"MAPPING",MEDUIM);
   Box(80,60+5*18,240,75+5*18,menu,46,"CREDITS",MEDUIM);
   Box(80,60+6*18,240,75+6*18,menu,46,"EXIT"   ,MEDUIM);
   Box(297,184,319,199,menu,46,"0",MEDUIM);
   for(i=187;i<196;i++)
   movedata(FP_SEG(lib),FP_OFF(lib)+1024*62,
            FP_SEG(menu),FP_OFF(menu)+300+i*320,16);
   Text_Small(299,188,"IMG",NORMAL,menu);

   Box(160-120,15,160+120,50,menu,46,"",SMALL);
   Text(58,20,"GRAPHICAL TOOLBOX",STRETCH,menu);
   Box(160-7*7,15,160+7*7,24,menu,49,"Charles Watkins",SMALL);
   movedata(FP_SEG(menu),FP_OFF(menu),0xA000,0x00,0xFA00);

   if(tile==0 ) i=42;
   if(tile==1 ) i=43;
   if(tile==2 ) i=44;
   if(tile==3 ) i=45;
   if(tile==4 ) i=46;
   if(tile==5 ) i=48;
   if(tile==6 ) i=49;
   if(tile==7 ) i=50;
   if(tile==8 ) i=51;
   if(tile==9 ) i=52;
   if(tile==10) i=60;
   if(tile==11) i=61;

   Box(0,0,319,199,menu,i,""                   ,SMALL);
   Box(88,60+0*18,232,75+0*18,menu,45,"NEW"    ,NORMAL);
   Box(88,60+1*18,232,75+1*18,menu,45,"LOAD"   ,NORMAL);
   Box(88,60+2*18,232,75+2*18,menu,45,"SAVE"   ,NORMAL);
   Box(88,60+3*18,232,75+3*18,menu,45,"EDITING",NORMAL);
   Box(88,60+4*18,232,75+4*18,menu,45,"MAPPING",NORMAL);
   Box(88,60+5*18,232,75+5*18,menu,45,"CREDITS",NORMAL);
   Box(88,60+6*18,232,75+6*18,menu,45,"EXIT"   ,NORMAL);
   Box(297,184,319,199,menu,45,"",NORMAL);
   for(i=187;i<196;i++)
   movedata(FP_SEG(lib ),FP_OFF(lib )+1024*62,
            FP_SEG(menu),FP_OFF(menu)+300+i*320,16);
   Text_Small(299,188,"IMG",NORMAL,menu);
   movedata(0xA000,0x00,FP_SEG(scrap),FP_OFF(scrap),0xFA00);
   change=0;
  }





  oX=X,oY=Y;
  Mouse_Status();

  if(BUTTON==3) exit=YES;

  sy+=3; if(sy>359) sy-=360;
  movedata(FP_SEG(scrap),FP_OFF(scrap),FP_SEG(scn),FP_OFF(scn),0xFA00);

  a=0;
  for(e=0;e<7;e++)
  for(i=0;i<32;i++)
  {
  if(3+e*32+i<197)
  movedata(FP_SEG(menu),FP_OFF(menu)+fiz[a]+23+(3+i)*320,
           FP_SEG(scn ),FP_OFF(scn )+       23+(3+i+e*32)*320,274);
  a++; if(a>35) a=0;
  }
  for(i=15;i<50;i++)
  movedata(FP_SEG(scrap),FP_OFF(scrap)+40+(i)*320,
           FP_SEG(scn  ),FP_OFF(scn  )+40+(i)*320,240);

  for(e=0;e<7;e++)
  {
   if(e==item) continue;
   for(i=0;i<15;i++)
   movedata(FP_SEG(scrap),FP_OFF(scrap)+80+(e*18+60+i)*320,
            FP_SEG(scn  ),FP_OFF(scn  )+80+(e*18+60+i)*320,160);
  }
  if(item!=7)
  for(i=0;i<15;i++)
  movedata(FP_SEG(menu),FP_OFF(menu)+88+(item*18+60+i)*320,
           FP_SEG(scn ),FP_OFF(scn )+88+(item*18+60+i)*320,144);
  else
  for(i=184;i<199;i++)
  movedata(FP_SEG(menu),FP_OFF(menu)+297+i*320,
           FP_SEG(scn ),FP_OFF(scn )+297+i*320,23);

  a=fiz[0];
  for(i=1;i<36;i++) fiz[i-1]=fiz[i];
  fiz[35]=a;


  d+=10; if(d>359) d-=359;
  for(a=0;a<5;a++)
  for(i=0;i<18;i++)
  {
   c=d+i+a*18; if(c>359) c-=360;if(c>359) c-=360;
   Spin(30,0,0,0,0,c);

   Spin(cz,cx,cy,0,0,i*20);
   star[0][i+a*18]=cx;
   star[1][i+a*18]=cy;
   star[2][i+a*18]=cz;
  }

  for(a=0;a<90;a++)
  {
   Spin(star[0][a],star[1][a],star[2][a],sy,20,359-sy);
   floatx=((float)cx/((float)cz+160))*160;
   floaty=((float)cy/((float)cz+160))*160;
   points[a][0]=int(floatx); points[a][1]=int(floaty);
  }

  for(a=0;a<5;a++)
  for(i=0;i<18;i++)
  {
   if(i<17)
   Line(points[  i+a*18][0]+40,points[  i+a*18][1]+100,
        points[1+i+a*18][0]+40,points[1+i+a*18][1]+100,32*4+10+a*2,scn);
   else
   Line(points[i+a*18][0]+40,points[i+a*18][1]+100,
        points[0+a*18][0]+40,points[0+a*18][1]+100,32*4+10+a*2,scn);

   if(a<4)
   Line(points[   i+a*18][0]+40,points[   i+a*18][1]+100,
        points[18+i+a*18][0]+40,points[18+i+a*18][1]+100,32*2+10+a*2,scn);

   if(i<17)
   Line(-1*points[  i+a*18][0]+280,-1*points[  i+a*18][1]+100,
        -1*points[1+i+a*18][0]+280,-1*points[1+i+a*18][1]+100,32*2+10+a*2,scn);
   else
   Line(-1*points[i+a*18][0]+280,-1*points[i+a*18][1]+100,
        -1*points[0+a*18][0]+280,-1*points[0+a*18][1]+100,32*2+10+a*2,scn);

   if(a<4)
   Line(-1*points[   i+a*18][0]+280,-1*points[   i+a*18][1]+100,
        -1*points[18+i+a*18][0]+280,-1*points[18+i+a*18][1]+100,32*4+10+a*2,scn);
  }


  for(a=0;a<90;a++)
  {
   pokeb(FP_SEG(scn),FP_OFF(scn)+-1*points[a][0]+-1*points[a][1]*320+32040,32*4-1);
   pokeb(FP_SEG(scn),FP_OFF(scn)+points[a][0]+points[a][1]*320+32280,32*4-1);
  }

  if((oX!=X) || (oY!=Y))
  {
   if((X>80) && (X<240) && (Y>60+0*18) && (Y<75+0*18)) item=0;
   if((X>80) && (X<240) && (Y>60+1*18) && (Y<75+1*18)) item=1;
   if((X>80) && (X<240) && (Y>60+2*18) && (Y<75+2*18)) item=2;
   if((X>80) && (X<240) && (Y>60+3*18) && (Y<75+3*18)) item=3;
   if((X>80) && (X<240) && (Y>60+4*18) && (Y<75+4*18)) item=4;
   if((X>80) && (X<240) && (Y>60+5*18) && (Y<75+5*18)) item=5;
   if((X>80) && (X<240) && (Y>60+6*18) && (Y<75+6*18)) item=6;
   if((X>297) && (X<319) && (Y>184) && (Y<199)) item=7;
  }
  Draw_Mouse();
  if((X>80) && (X<240) && (Y>60+0*18) && (Y<75+0*18) && (BUTTON==1)) bb=0;
  if((X>80) && (X<240) && (Y>60+1*18) && (Y<75+1*18) && (BUTTON==1)) bb=1;
  if((X>80) && (X<240) && (Y>60+2*18) && (Y<75+2*18) && (BUTTON==1)) bb=2;
  if((X>80) && (X<240) && (Y>60+3*18) && (Y<75+3*18) && (BUTTON==1)) bb=3;
  if((X>80) && (X<240) && (Y>60+4*18) && (Y<75+4*18) && (BUTTON==1)) bb=4;
  if((X>80) && (X<240) && (Y>60+5*18) && (Y<75+5*18) && (BUTTON==1)) bb=5;
  if((X>80) && (X<240) && (Y>60+6*18) && (Y<75+6*18) && (BUTTON==1)) bb=6;
  if((X>297) && (X<319) && (Y>179) && (Y<199) && (BUTTON==1)) bb=7;
  if((X>80) && (X<240) && (Y>60+0*18) && (Y<75+0*18) && (BUTTON==0) &&
     (bb==0)) {  Beep(); New(); change=1; }
  if((X>80) && (X<240) && (Y>60+1*18) && (Y<75+1*18) && (BUTTON==0) &&
     (bb==1)) {  Beep(); Load(); change=1; }
  if((X>80) && (X<240) && (Y>60+2*18) && (Y<75+2*18) && (BUTTON==0) &&
     (bb==2)) {  Beep(); Save(); change=1; }
  if((X>80) && (X<240) && (Y>60+3*18) && (Y<75+3*18) && (BUTTON==0) &&
     (bb==3)) {  Beep(); Editing(); change=1; }
  if((X>80) && (X<240) && (Y>60+4*18) && (Y<75+4*18) && (BUTTON==0) &&
     (bb==4)) {  Beep(); Mapping(); change=1; }
  if((X>80) && (X<240) && (Y>60+5*18) && (Y<75+5*18) && (BUTTON==0) &&
     (bb==5)) {  Beep(); Credits(); change=1; }
  if((X>80) && (X<240) && (Y>60+6*18) && (Y<75+6*18) && (BUTTON==0) &&
     (bb==6)) {  Beep(); Fade_Out(); exit=YES; }
  if((X>298) && (X<319) && (Y>179) && (Y<199) && (BUTTON==0) && (bb==7))
  { Beep(); tile++; if(tile>11) tile=0; change=1; }

  if(BUTTON==0) bb=9;
 }
}

void Credits(void)
{
 Fade_Out();
int tnum=48;
char *txt[48]={ "",                       //1
                "Credits",          "",   // 2
                "","","","",              // 4
                "Layout",                 // 1
                "Charles Watkins",  "",   // 2
                "","",                    // 2
                "Logic Design",           // 1
                "Charles Watkins",  "",   // 2
                "","",                    // 2
                "3D Engine",              // 1
                "Charles Watkins",  "",   // 2
                "","",                    // 2
                "Programming",            // 1
                "Charles Watkins",  "",   // 2
                "","",                    // 2
                "Lead Artist",            // 1
                "Charles Watkins",  "",   // 2
                "","",                    // 2
                "Beta Testers",           // 1
                "Charles Watkins",  "",   // 2
                "","","","",              // 4
                "Cool Huh",               // 1
                "","","","",              // 4
                "","","","",              // 4
                };

 int a,b,c,e,i,red[64],star[4][20],fiz[32],exit=NO;
 int fuzz[200];
 void *buf;
 buf=MK_FP(FP_SEG(menu),FP_OFF(menu)+39*320);
 for(i=0;i<200;i++) fuzz[i]=random(20);
 for(e=0;e<10;e++)
 for(i=0;i<7;i++)
 for(c=0;c<32;c++)
 if((c+i*32<=170) && (c+i*32>=30))
 movedata(FP_SEG(lib),FP_OFF(lib)+1024*48+c*32,
          FP_SEG(scn),FP_OFF(scn)+e*32+(c+i*32)*320,32);

 Box(10,50,310,150,scn,46,"",SMALL);

 for(i=53;i<147;i++)
 movedata(FP_SEG(lib),FP_OFF(lib)+1024*62,
          FP_SEG(scn),FP_OFF(scn)+15+i*320,290);


 for(a=0;a<10;a++)
 {
 for(i=0;i<32;i++)
 movedata(FP_SEG(lib),FP_OFF(lib)+44*1024+i*32,
          FP_SEG(scn),FP_OFF(scn)+a*32+i*320,32);
 for(i=0;i<32;i++)
 movedata(FP_SEG(lib),FP_OFF(lib)+44*1024+i*32,
          FP_SEG(scn),FP_OFF(scn)+a*32+i*320+168*320,32);
 }

 for(a=0;a<20;a++)
 {
  star[0][a]=random(160)+80;
  star[1][a]=random(100)+50;
  star[2][a]=random(4);
  star[3][a]=32*7+10+(3-star[2][a]*4)+random(6);
 }
 for(a=0;a<32;a++) fiz[a]=random(64);
 fiz[0]=0;
 for(a=0;a<32;a++) red[a]=a*2;
 for(a=0;a<32;a++) red[32+a]=64-a*2;

 e=16,c=-1,b=0;

 movedata(FP_SEG(scn  ),FP_OFF(scn  ),
          FP_SEG(scrap),FP_OFF(scrap),0xFA00);

 memset(buf,36,27*320);

 while(exit!=YES)
 {
  Mouse_Status();



  b++; if(b>1) { b=0; e++; }
  if(e>24)
  {
   e=0; c++;
   if(c>tnum-1) { c=0;  }
   memset(buf,36,27*320);
   Text_Big(168-strlen(txt[c])*10,0,txt[c],PASTE,buf);
  }

  for(i=53;i<147;i++)
    movedata(FP_SEG(scrap),FP_OFF(scrap)+15+i*320+320,
             FP_SEG(scrap),FP_OFF(scrap)+15+i*320,290);


  if(b==0)
   movedata(FP_SEG(menu ),FP_OFF(menu )+15+e*320+39*320,
            FP_SEG(scrap),FP_OFF(scrap)+15+146*320,290);
  else
   movedata(FP_SEG(menu  ),FP_OFF(menu  )+15+26*320+39*320,
            FP_SEG(scrap),FP_OFF(scrap)+15+146*320,290);

  movedata(FP_SEG(scrap),FP_OFF(scrap),
           FP_SEG(scn  ),FP_OFF(scn  ),0xFA00);

  for(i=168;i<200;i++)
  movedata(FP_SEG(scn  ),FP_OFF(scn  )+i*320,
           FP_SEG(scrap),FP_OFF(scrap)+i*320+3,317);
  for(i=168;i<200;i++)
  movedata(FP_SEG(scn  ),FP_OFF(scn  )+i*320+317,
           FP_SEG(scrap),FP_OFF(scrap)+i*320,3);
  for(i=0;i<32;i++)
  movedata(FP_SEG(scn  ),FP_OFF(scn  )+i*320+3,
           FP_SEG(scrap),FP_OFF(scrap)+i*320,317);
  for(i=0;i<32;i++)
  movedata(FP_SEG(scn  ),FP_OFF(scn  )+i*320,
           FP_SEG(scrap),FP_OFF(scrap)+i*320+317,3);

if(random(100)>190)
  {
   for(i=53;i<147;i++)
   movedata(FP_SEG(scrap),FP_OFF(scrap)+i*320+15,
            FP_SEG(scn  ),FP_OFF(scn  )+i*320+15+fuzz[i],290-fuzz[i]);
   for(i=53;i<147;i++)
   movedata(FP_SEG(scrap),FP_OFF(scrap)+i*320+15+fuzz[i],
            FP_SEG(scn  ),FP_OFF(scn  )+i*320+15,fuzz[i]);
   a=fuzz[0];
   for(i=0;i<199;i++) fuzz[i]=fuzz[i+1];
   fuzz[199]=a;
  }

  if((X<20) && (Y<10))
  {
    drawmouse=NO;
    for(i=0;i<32;i++)
    movedata(FP_SEG(lib),FP_OFF(lib)+1024*47+i*32,
             FP_SEG(scn),FP_OFF(scn)+i*320,32);
  }
  else
  if((X>300) && (Y<10))
  {
    drawmouse=NO;
    for(i=0;i<32;i++)
    movedata(FP_SEG(lib),FP_OFF(lib)+1024*47+i*32,
             FP_SEG(scn),FP_OFF(scn)+288+i*320,32);
  }
  else
  if((X<20) && (Y>190))
  {
    drawmouse=NO;
    for(i=0;i<32;i++)
    movedata(FP_SEG(lib),FP_OFF(lib)+1024*47+i*32,
             FP_SEG(scn),FP_OFF(scn)+(167+i)*320,32);
  }
  else
  if((X>300) && (Y>190))
  {
    drawmouse=NO;
    for(i=0;i<32;i++)
    movedata(FP_SEG(lib),FP_OFF(lib)+1024*47+i*32,
             FP_SEG(scn),FP_OFF(scn)+288+(167+i)*320,32);
  }
  else
  drawmouse=YES;

  if((((X<20) && (Y<10 )) || ((X>300) && (Y<10)) ||
      ((X<20) && (Y>190)) || ((X>300) && (Y>190))) && (BUTTON==1)) exit=YES;

  a=fiz[1];
  for(i=2;i<32;i++) fiz[i-1]=fiz[i];
  fiz[31]=a;
  a=red[0];
  for(i=1;i<64;i++) red[i-1]=red[i];
  red[63]=a;
  for(i=0;i<32;i++)
  {
   Pal[i*3]=fiz[i];
   Pal[i*3+1]=fiz[i];
   Pal[i*3+2]=fiz[i];
   Pal[32*4*3+i*3]=0;
   Pal[32*4*3+i*3+1]=i*2;
   Pal[32*4*3+i*3+2]=0;
  }


  for(a=0;a<20;a++)
  {
   star[1][a]=star[1][a]-(4-star[2][a]);
   if(star[1][a]<50) star[1][a]=148;
   if(peekb(FP_SEG(scn),FP_OFF(scn)+star[0][a]+star[1][a]*320)==36)
   pokeb(FP_SEG(scn),FP_OFF(scn)+star[0][a]+star[1][a]*320,star[3][a]);
  }
  Set_VGA_Palette();
  Draw_Mouse();
 }
 drawmouse=YES;
 Fade_Out();
 Set_All_Palette();
}

void Load(void)
{
 int a,b,c,e=0,f=0,g=70,i,j=0,x=0,y=0,z=0,ob,oy=1,oz=0,sc=0,Stars[100][4],
     points[100][2],exit=NO;
 char file[50][13],fiz[32];
 float floatx,floaty;
 struct ffblk ffblk;

 Box(0  ,0  ,319,199,scn,50,"" ,SMALL);
 Box(60 ,25 ,240,175,scn,46,"" ,SMALL);

 Box(240,50 ,260,100,scn,46,"" ,MEDUIM);
 Box(240,100,260,150,scn,46,"" ,MEDUIM);
 Box(240,25 ,260,50 ,scn,46,"*",MEDUIM);
 Box(240,150,260,176,scn,46,"@",MEDUIM);
 Text_Big(18,50,"LOAD",DOWN,scn);
 Text_Big(282,50,"LOAD",DOWN,scn);

 for(i=28;i<172;i++)
 movedata(FP_SEG(lib),FP_OFF(lib)+1024*62,
          FP_SEG(scn),FP_OFF(scn)+63+i*320,173);
 movedata(FP_SEG(scn  ),FP_OFF(scn  ),
          FP_SEG(scrap),FP_OFF(scrap),0xFA00);

 b=0;

 exit=findfirst("*.LIB",&ffblk,0);

 for(a=0;a<32;a++) fiz[a]=random(64);
 fiz[0]=0;


 while(!exit)
 {
  for(a=0;a<13;a++) file[x][a]=ffblk.ff_name[a];
  exit=findnext(&ffblk);
  x++; if(x>49) break;
 }
  if(x!=0) x--;
  else
  {
   j=1;
   char *txt="^  NO FILES  $";
   for(i=0;i<14;i++) file[0][i]=txt[i];
   file[0][14]=0;
  }
  exit=NO;

 while(exit!=YES)
 {
  ob=BUTTON;
  Mouse_Status();

  if((oy!=y) || (oz!=z))
  {
   Box(60 ,25 ,240,175,scrap,46,"" ,SMALL);
   for(i=28;i<172;i++)
   movedata(FP_SEG(lib  ),FP_OFF(lib  )+1024*62,
            FP_SEG(scrap),FP_OFF(scrap)+63+i*320,173);
   if(x<10) a=x; else a=9;
   for(i=0;i<a;i++) Text(70,32+i*15,file[i+y],PASTE,scrap);
   if(f==0)
   Box(60 ,29+z*15 ,240,47+z*15,scrap,48,"",MEDUIM);
   else
   Box(60 ,29+z*15 ,240,47+z*15,scrap,46,"",MEDUIM);
   for(i=31+z*15;i<45+z*15;i++)
   movedata(FP_SEG(lib  ),FP_OFF(lib  )+1024*62,
            FP_SEG(scrap),FP_OFF(scrap)+63+i*320,173);
   Text(70,32+z*15,file[z+y],PASTE,scrap);
  }

  oy=y,oz=z;

  if((X>60) && (X<240) && (Y>15  ) && (Y<175)) { z=(Y-15)/15-1; }

  if((X>240) && (X<260) && (Y>50 ) && (Y<100) && (BUTTON==1) && (ob!=BUTTON)) { y-=7; z=0; }
  if((X>240) && (X<260) && (Y>100) && (Y<150) && (BUTTON==1) && (ob!=BUTTON)) { y+=7; z=8; }
  if((X>240) && (X<260) && (Y>25 ) && (Y<50 ) && (BUTTON==1) && (ob!=BUTTON)) { z--;  }
  if((X>240) && (X<260) && (Y>150) && (Y<175) && (BUTTON==1) && (ob!=BUTTON)) { z++;  }
  if(z<0) { y--; z=0; }
  if(x<8) a=x; else a=8;
  if(z>a) { z=a; y++; }
  if(y>x-8) y=x-8;
  if(y<0)   y=0;

  if((X>60) && (X<240) && (Y>z*15+30) && (Y<z*15+48) && (BUTTON==0) && (f==1))
  {
   g=y+z;
   exit=YES;
   Beep();
  }

  if(((X<60) || (X>240) || (Y<z*15+30) || (Y>z*15+48)) && (f==1))
  {
   f=0;
   Box(60 ,29+z*15 ,240,47+z*15,scrap,48,"",MEDUIM);
   for(i=31+z*15;i<45+z*15;i++)
   movedata(FP_SEG(lib  ),FP_OFF(lib  )+1024*62,
            FP_SEG(scrap),FP_OFF(scrap)+63+i*320,173);
   Text(70,32+z*15,file[z+y],PASTE,scrap);
  }

  if((BUTTON==0) && (f==1))
  {
   f=0;
   Box(60 ,29+z*15 ,240,47+z*15,scrap,48,"",MEDUIM);
   for(i=31+z*15;i<45+z*15;i++)
   movedata(FP_SEG(lib  ),FP_OFF(lib  )+1024*62,
            FP_SEG(scrap),FP_OFF(scrap)+63+i*320,173);
   Text(70,32+z*15,file[z+y],PASTE,scrap);
  }

  if((X>60) && (X<240) && (Y>z*15+30) && (Y<z*15+48) && (BUTTON==1) && (f!=1))
  {
   f=1;
   Box(60 ,29+z*15 ,240,47+z*15,scrap,46,"",MEDUIM);
   for(i=31+z*15;i<45+z*15;i++)
   movedata(FP_SEG(lib  ),FP_OFF(lib  )+1024*62,
            FP_SEG(scrap),FP_OFF(scrap)+63+i*320,173);
   Text(70,32+z*15,file[z+y],PASTE,scrap);
  }



  if((X>240) && (X<260) && (Y>50) && (Y<100) && (sc!=1))
  {
   if(sc==2) Box(240,100,260,150,scrap,46,"",MEDUIM);
   if(sc==3) Box(240,25 ,260,50 ,scrap,46,"*",MEDUIM);
   if(sc==4) Box(240,150,260,175,scrap,46,"@",MEDUIM);
   Box(240,50 ,260,100,scrap,45,"",MEDUIM);
   sc=1;
  }

  if((X>240) && (X<260) && (Y>100) && (Y<150) && (sc!=2))
  {
   if(sc==1) Box(240,50 ,260,100,scrap,46,"",MEDUIM);
   if(sc==3) Box(240,25 ,260,50 ,scrap,46,"*",MEDUIM);
   if(sc==4) Box(240,150,260,175,scrap,46,"@",MEDUIM);
   Box(240,100,260,150,scrap,45,"",MEDUIM);
   sc=2;
  }

  if((X>240) && (X<260) && (Y>25) && (Y<50) && (sc!=3))
  {
   if(sc==1) Box(240,50 ,260,100,scrap,46,"",MEDUIM);
   if(sc==2) Box(240,100,260,150,scrap,46,"",MEDUIM);
   if(sc==4) Box(240,150,260,175,scrap,46,"@",MEDUIM);
   Box(240,25 ,260,50 ,scrap,45,"*",MEDUIM);
   sc=3;
  }

  if((X>240) && (X<260) && (Y>150) && (Y<175) && (sc!=4))
  {
   if(sc==1) Box(240,50 ,260,100,scrap,46,"",MEDUIM);
   if(sc==2) Box(240,100,260,150,scrap,46,"",MEDUIM);
   if(sc==3) Box(240,25 ,260,50 ,scrap,46,"*",MEDUIM);
   Box(240,150,260,175,scrap,45,"@",MEDUIM);
   sc=4;
  }

  if(((X<240) || (X>260) || (Y<25) || (Y>175)) && (sc!=0))
  {
   Box(240,50 ,260,100,scrap,46,"",MEDUIM);
   Box(240,100,260,150,scrap,46,"",MEDUIM);
   Box(240,25 ,260,50 ,scrap,46,"*",MEDUIM);
   Box(240,150,260,175,scrap,46,"@",MEDUIM);
   sc=0;
  }

   movedata(FP_SEG(scrap),FP_OFF(scrap),
            FP_SEG(scn  ),FP_OFF(scn  ),0xFA00);


  b++; if(b>359) b-=359;

  e+=10; if(e>359) e-=359;
  for(a=0;a<10;a++)
  for(i=0;i<10;i++)
  {
   c=e+i+a*10; if(c>359) c-=360;
   Spin(a*2+5,0,0,0,0,c);
   Spin(5+a*3,0,cx,0,0,i*36);
   Stars[i+a*10][0]=cx;
   Stars[i+a*10][1]=cy;
   Stars[i+a*10][2]=cz;
  }

  for(a=0;a<10;a++)
  for(i=0;i<10;i++)
  {
   Spin(Stars[i+a*10][0],Stars[i+a*10][1],Stars[i+a*10][2],b,b,b);
   floatx=((float)cx/((float)cz+160))*160;
   floaty=((float)cy/((float)cz+160))*160;
   points[i+a*10][0]=int(floatx); points[i+a*10][1]=int(floaty);
  }

  for(a=0;a<10;a++)
  for(i=0;i<10;i++)
  {
   if(i<9)
   Line(points[  i+a*10][0]+30,points[  i+a*10][1]+100,
        points[1+i+a*10][0]+30,points[1+i+a*10][1]+100,32*7+10+a*2,scn);
   else
   Line(points[i+a*10][0]+30,points[i+a*10][1]+100,
        points[0+a*10][0]+30,points[0+a*10][1]+100,32*7+10+a*2,scn);

   if(a<9)
   Line(points[   i+a*10][0]+30,points[   i+a*10][1]+100,
        points[10+i+a*10][0]+30,points[10+i+a*10][1]+100,32*7+10+a*2,scn);

   if(i<9)
   Line(-1*points[  i+a*10][0]+290,points[  i+a*10][1]+100,
        -1*points[1+i+a*10][0]+290,points[1+i+a*10][1]+100,32*7+10+a*2,scn);
   else
   Line(-1*points[i+a*10][0]+290,points[i+a*10][1]+100,
        -1*points[0+a*10][0]+290,points[0+a*10][1]+100,32*7+10+a*2,scn);

   if(a<9)
   Line(-1*points[   i+a*10][0]+290,points[   i+a*10][1]+100,
        -1*points[10+i+a*10][0]+290,points[10+i+a*10][1]+100,32*7+10+a*2,scn);
  }


  if((X<20) && (Y<10))
   {
     drawmouse=NO;
     for(i=0;i<32;i++)
     movedata(FP_SEG(lib),FP_OFF(lib)+1024*47+i*32,
              FP_SEG(scn),FP_OFF(scn)+i*320,32);
   }
   else
   if((X>300) && (Y<10))
   {
     drawmouse=NO;
    for(i=0;i<32;i++)
     movedata(FP_SEG(lib),FP_OFF(lib)+1024*47+i*32,
              FP_SEG(scn),FP_OFF(scn)+288+i*320,32);
   }
   else
   if((X<20) && (Y>190))
   {
     drawmouse=NO;
     for(i=0;i<32;i++)
     movedata(FP_SEG(lib),FP_OFF(lib)+1024*47+i*32,
              FP_SEG(scn),FP_OFF(scn)+(167+i)*320,32);
   }
   else
   if((X>300) && (Y>190))
   {
     drawmouse=NO;
     for(i=0;i<32;i++)
     movedata(FP_SEG(lib),FP_OFF(lib)+1024*47+i*32,
              FP_SEG(scn),FP_OFF(scn)+288+(167+i)*320,32);
   }
   else
   drawmouse=YES;

   if((((X<20) && (Y<10 )) || ((X>300) && (Y<10)) ||
       ((X<20) && (Y>190)) || ((X>300) && (Y>190))) && (BUTTON==1))
       exit=YES;

   a=fiz[1];
  for(i=2;i<32;i++) fiz[i-1]=fiz[i];
  fiz[31]=a;
  for(i=0;i<32;i++)
  {
   Pal[i*3]=fiz[i];
   Pal[i*3+1]=fiz[i];
   Pal[i*3+2]=fiz[i];
  }
  Set_VGA_Palette();
 Draw_Mouse();
  }
 if((g<60) && (j==0))
 {
  FILE *dat;
  dat=fopen(file[g],"rb");
  fread(data,0xFC00,1,dat);
  fclose(dat);
  sprintf(filename,"%s",file[g]);
  file_open=YES;
  Obj=0;
  movedata(FP_SEG(data),FP_OFF(data)+Obj*1024,
           FP_SEG(clip),FP_OFF(clip),1024);
 }
 drawmouse=YES;
 Set_All_Palette();
}

void Save(void)
{
 int exit=NO,a=0,b=3;
 if(file_open==NO) { Prompt("No File to Save!"); return; }

 Box(60,80,260,125,scn,46,"",SMALL);
 Box(70,100,155,120,scn,52,"YES",MEDUIM);
 Box(165,100,250,120,scn,52,"NO",MEDUIM);
 Text_Small(160-19*3,90,"Do You Want To Save",SINK,scn);

 while(exit!=YES)
 {
  a=BUTTON;
  Mouse_Status();

  if((X>70) && (X<155) && (Y>100) && (Y<120))
  {
   if(BUTTON==0)   Box(70,100,155,120,scn,52,"YES",NORMAL);
   if(BUTTON==1)   Box(70,100,155,120,scn,45,"YES",NORMAL);
   Box(165,100,250,120,scn,46,"NO",DOWN);
   if((BUTTON==0) && (a==1)) { exit=YES; b=0; }
  }

  if((X>165) && (X<250) && (Y>100) && (Y<120))
  {
   Box(70,100,155,120,scn,46,"YES",DOWN);
   if(BUTTON==0) Box(165,100,250,120,scn,52,"NO",NORMAL);
   if(BUTTON==1) Box(165,100,250,120,scn,45,"NO",NORMAL);
   if((BUTTON==0) && (a==1)) { exit=YES; b=1; }
  }

  if((X<70) || (X>250) || (Y<100) || (Y>120))
  {
   Box(70,100,155,120,scn,46,"YES",MEDUIM);
   Box(165,100,250,120,scn,46,"NO",MEDUIM);
  }

  Draw_Mouse();
 }
 if(b==0)
 {
  FILE *file;
  file=fopen(filename,"w+b");
  fwrite(data,0xFC00,1,file);
  fclose(file);
 }
}


void New(void)
{
 setvect(0x09,Old_Key_Isr);
 int a=0,b,c=1,x,y,i,exit=NO,fuz[200];
 float px[100],py[100],pz[100],ps[100],pc[100];
 float x1,y1;
 char txt[9],dir=-1;
 unsigned int f=0,ppct=60,oppct=0;
 randomize();

 for(i=0;i<100;i++)
 {
    pz[i]=-100;
    px[i]=random(320)-160;
    py[i]=random(200)-100;
    ps[i]=random(8)+1;
    pc[i]=ps[i]*4+32*6;
 }

 for(b=0;b<9;b++) txt[b]=0;
 Box(0  ,0 ,320,199,scrap,45,"" ,SMALL);
 Text_Big(20 ,61,"NEW",DOWN,scrap);
 Text_Big(280,61,"LIB",DOWN,scrap);
 Box(40,8  ,280,30 ,scrap,50,"Please enter your eight digit file name" ,SMALL);
 Box(40,160,280,182,scrap,52,"",SMALL);
 Box(59,39 ,261,151,scrap,46,"",SMALL);
 for(i=43;i<147;i++)
 movedata(FP_SEG(lib  ),FP_OFF(lib  )+1024*62,
          FP_SEG(scrap),FP_OFF(scrap)+63+i*320,194);

 for(i=0;i<200;i++) fuz[i]=random(10)+10;

 movedata(FP_SEG(scn),FP_OFF(scn),FP_SEG(menu),FP_OFF(menu),0xFA00);

 for(a=0;a<32;a++)
 {
  for(i=0;i<200;i+=2)
  {
    if(fuz[i]*a<320)
     movedata(FP_SEG(menu),FP_OFF(menu)+i*320+fuz[i]*a,
              FP_SEG(scn ),FP_OFF(scn )+i*320,320-fuz[i]*a);
    if(fuz[i+1]*a<320)
     movedata(FP_SEG(menu),FP_OFF(menu)+i*320+320,
              FP_SEG(scn ),FP_OFF(scn )+i*320+320+fuz[i+1]*a,320-fuz[i+1]*a);
  }
  for(i=0;i<200;i+=2)
  {
    if(fuz[i]*a<320)
     movedata(FP_SEG(scrap),FP_OFF(scrap)+i*320+320-fuz[i]*a,
              FP_SEG(scn  ),FP_OFF(scn  )+i*320+320-fuz[i]*a,fuz[i]*a);
    if(fuz[i+1]*a<320)
     movedata(FP_SEG(scrap),FP_OFF(scrap)+i*320+320,
              FP_SEG(scn  ),FP_OFF(scn  )+i*320+320,fuz[i+1]*a);
  }
  movedata(FP_SEG(scn),FP_OFF(scn),0xA000,0x00,0xFA00);
 }
 a=0;
 while(kbhit()!=0) getch();

 while(exit!=YES)
 {
  movedata(FP_SEG(scrap),FP_OFF(scrap),FP_SEG(scn),FP_OFF(scn),0xFA00);
  Mouse_Status();

  f++;
  if(f>20)
  {
   for(i=0;i<3;i++)
   movedata(FP_SEG(lib),FP_OFF(lib)+1024*50+i*32,
            FP_SEG(scn),FP_OFF(scn)+i*320+178*320+160+6*a-12,11);
   if(f>40) f=0;
  }

  if(oppct<60) { oppct++; ppct=oppct; }

  for(i=0;i<100;i++)
  {
   pz[i]-=ps[i]*dir;
   Spin2(px[i],py[i],pz[i],0,0,5);
   px[i]=cx,py[i]=cy,pz[i]=cz;
   if(cz+ppct!=0)
   {
    x1=((float)(cx)/(float)(cz+ppct))*ppct;
    y1=((float)(cy)/(float)(cz+ppct))*ppct;
   } else { x1=cx; y1=cy; }

   x=int(x1);
   y=int(y1);
   if((x>-100) && (x<100 ) && (y>-50) && (y<50))
   pokeb(FP_SEG(scn),FP_OFF(scn)+x+y*320+32160,pc[i]);
   else
   {
    if(dir== 1) pz[i]=-100; else
    if(dir==-1) pz[i]=-200;
    px[i]=random(320)-160;
    py[i]=random(200)-100;
    ps[i]=random(8)+1;
    pc[i]=ps[i]*4+32*6;
   }
   if((pz[i]<-200) || (pz[i]>-100))
   {
     if(dir== 1) pz[i]=-100; else
     if(dir==-1) pz[i]=-200;
     px[i]=random(320)-160;
     py[i]=random(200)-100;
     ps[i]=random(8)+1;
     pc[i]=ps[i]*4+32*6;
   }
  }

  while(kbhit()!=0)
  {
   b=toupper(getch());
   if(((b>='A') && (b<='Z')) || ((b>='0') && (b<='9')))
   {
    if(a<8)
    {
     txt[a]=b; a++;
     Box(40,160,280,182,scrap,52,txt,DOWN);
    }
    else Beep();
   }
   if(b=='+') ppct++;
   if(b=='-') ppct--;
   if(b=='*') dir=-1;
   if(b=='/') dir=1;
   if(ppct<10) ppct=10; if(ppct>200) ppct=200;
   if(b==8)
   {
    if(a==0) a++;
    a--; txt[a]=0;
    Box(40,160,280,182,scrap,52,txt,DOWN);
   }
   if(b==13) { exit=YES; }
  }

  if((X<20) && (Y<10))
   {
     drawmouse=NO;
     for(i=0;i<32;i++)
     movedata(FP_SEG(lib),FP_OFF(lib)+1024*47+i*32,
              FP_SEG(scn),FP_OFF(scn)+i*320,32);
   }
   else
   if((X>300) && (Y<10))
   {
     drawmouse=NO;
    for(i=0;i<32;i++)
     movedata(FP_SEG(lib),FP_OFF(lib)+1024*47+i*32,
              FP_SEG(scn),FP_OFF(scn)+288+i*320,32);
   }
   else
   if((X<20) && (Y>190))
   {
     drawmouse=NO;
     for(i=0;i<32;i++)
     movedata(FP_SEG(lib),FP_OFF(lib)+1024*47+i*32,
              FP_SEG(scn),FP_OFF(scn)+(168+i)*320,32);
   }
   else
   if((X>300) && (Y>190))
   {
     drawmouse=NO;
     for(i=0;i<32;i++)
     movedata(FP_SEG(lib),FP_OFF(lib)+1024*47+i*32,
              FP_SEG(scn),FP_OFF(scn)+288+(168+i)*320,32);
   }
   else
   drawmouse=YES;

   if((((X<20) && (Y<10 )) || ((X>300) && (Y<10)) ||
       ((X<20) && (Y>190)) || ((X>300) && (Y>190))) && (BUTTON==1))
       { c=0; exit=YES; }

  Draw_Mouse();
 }

 if((a>0) && (c==1))
 {
  char txt2[14];
  file_open=YES;
  sprintf(txt2,"%s.LIB",txt);
  for(a=0;a<14;a++) filename[a]=txt2[a];
  memset(data,0,0xFC00);
  Obj=0;
  movedata(FP_SEG(data),FP_OFF(data)+Obj*1024,
           FP_SEG(clip),FP_OFF(clip),1024);
 }
 drawmouse=YES;
 Old_Key_Isr=getvect(0x09);
 setvect(0x09,New_Key_Int);
}

void Editing(void)
{
 if(file_open==NO) { Prompt("Open a File to Edit!"); return; }
 int exit=NO,ob,drawpen=YES,draw_styles=YES,draw_tstyles=YES;
 int start=YES,draw_button=YES;
 int a,b,c,d,e,f,g,h,i,j,k;
 int button[4][2];
 char txt[13];
 char c1;

 Smear_Out();

 for(a=0;a<4;a++)
 for(b=0;b<2;b++) button[a][b]=0;
 sprintf(txt,"%s",filename);

 Box(0,0,319,199,menu,52,"",SMALL);
 Box(50,5,130,15,menu,45,txt,SMALL);

 Box(179,4,313,42,menu,52,"",SMALL);

 Box(180,44,200,62,menu,46,"$",BLEND);
 Box(292,44,312,62,menu,46,"^",BLEND);


 Box(180,127,217,196,menu,46,"",BLEND);

 for(i=0;i<32;i++)
 for(a=0;a<8;a++)
 for(b=0;b<4;b++)
 for(c=0;c<4;c++)
 pokeb(FP_SEG(menu),FP_OFF(menu)+182+b+a*4*320+i*4+7*320+c*320,i+a*32);

 movedata(FP_SEG(menu),FP_OFF(menu),
          FP_SEG(scn ),FP_OFF(scn ),0xFA00);

 Draw_Object();
 while(exit!=YES)
 {
  ob=BUTTON;
  Mouse_Status();

  if(Key[F1]==ON) size=1;
  if(Key[F2]==ON) size=2;
  if(Key[F3]==ON) size=3;
  if(Key[F4]==ON) size=4;
  if(Key[F5]==ON) size=5;
  if((Key[SPACE]==ON) && (Key[SHIFT]==ON )) { BUTTON=2; }
  if((Key[SPACE]==ON) && (Key[SHIFT]==OFF)) { BUTTON=1; }
  if((Key[SHIFT]==ON) && (Key[ALT ]==ON))
   if((X>=90 -16*size) && (X<=89+16*size) &&
      (Y>=100-16*size) && (Y<=99+16*size))
   {
    start=YES;
    a=(X-(90 -size*16))/size;
    b=(Y-(100-size*16))/size;
    color1=peekb(FP_SEG(clip),FP_OFF(clip)+a+b*32);
   }
  if((Key[SHIFT]==ON) && (Key[CTRL]==ON))
   if((X>=90 -16*size) && (X<=89+16*size) &&
     (Y>=100-16*size) && (Y<=99+16*size))
   {
    start=YES;
    a=(X-(90 -size*16))/size;
    b=(Y-(100-size*16))/size;
    color2=peekb(FP_SEG(clip),FP_OFF(clip)+a+b*32);
   }


  if((X>=90 -16*size) && (X<=89+16*size) &&
     (Y>=100-16*size) && (Y<=99+16*size))
       { drawmouse=NO;  drawpen=YES; }
  else { drawmouse=YES; drawpen=NO;  }


  if((X>220) && (X<240) && (Y>130) && (Y<194) && (BUTTON==1) && (ob!=1))
  size=(Y-130)/13+1;
  if((X>220) && (X<240) && (Y>130) && (Y<194) && (BUTTON==2))
  size=(Y-130)/13+1;

  if(((X>182) && (X<309) && (Y>7) && (Y<38)) || (start==YES))
  {
   for(h=7;h<39;h++)
   movedata(FP_SEG(menu),FP_OFF(menu)+h*320+180,
            FP_SEG(scn ),FP_OFF(scn )+h*320+180,130);
   a=(X-182)/4;
   b=(Y-7  )/4;
   e=a+15; if(e>31) e-=32;
   if(start==NO)
   for(d=0;d<4;d++)
   for(c=0;c<4;c++)
   if((d>0) && (d<3) && (c>0) && (c<3)) continue; else
   pokeb(FP_SEG(scn),FP_OFF(scn)+182+d+b*4*320+a*4+7*320+c*320,(8-b)*32+e);
   if(BUTTON==1) color1=a+b*32;
   if(BUTTON==2) color2=a+b*32;
   b=color1/32;
   a=color1-b*32;
   e=a+15; if(e>31) e-=32;
   for(d=0;d<4;d++) for(c=1;c<3;c++)
    pokeb(FP_SEG(scn),FP_OFF(scn)+182+d+b*4*320+a*4+7*320+c*320,(8-b)*32+e);
   b=color2/32;
   a=color2-b*32;
   e=a+15; if(e>31) e-=32;
   for(d=1;d<3;d++) for(c=0;c<4;c++)
    pokeb(FP_SEG(scn),FP_OFF(scn)+182+d+b*4*320+a*4+7*320+c*320,(8-b)*32+e);
   drawmouse=NO;
  }


  for(a=0;a<2;a++)
  for(b=0;b<2;b++)
  {
   c=0;
   if((X>=180+a*32) && (X<212+a*32) && (Y>=63+b*32) && (Y<95+b*32)) c=1;
   button[a*2+b][0]=0;
   if((c==1) && ((BUTTON==1) && (ob==0)))
   { button[a*2+b][0]=1; button[a*2+b][1]=1; }
   if((c==1) && (BUTTON==1) && (button[a*2+b][1]==1))
   { button[a*2+b][0]=1; }
   if(((c==1) && ((BUTTON==0) && (ob==1)) && (button[a*2+b][1]==1)) ||
      ((Key[ALT]==ON) && (Key[CTRL]==ON) && (BUTTON!=0)))
   {
    if((a==0) && (b==0)) if(WRAP==ON) WRAP=OFF; else WRAP=ON;
    if((a==1) && (b==0))
    {
     movedata(FP_SEG(clip),FP_OFF(clip),
              FP_SEG(clip),FP_OFF(clip)+1024*3,1024);
     Draw_Object();
    }
    if((a==1) && (b==1))
    {
     movedata(FP_SEG(clip),FP_OFF(clip)+1024*3,
              FP_SEG(clip),FP_OFF(clip),1024);
     Draw_Object();
    }
    button[a*2+b][1]=0;
    if((a==0) & (b==1))
    {
     TILE=ON;
     if(Tile_Mode==T_FILL    ) Pen_Draw    (0,0);
     if(Tile_Mode==T_X_BLEND ) Tile_XBlend (0,0);
     if(Tile_Mode==T_PAINT   ) Pen_Paint   (0,0);
     if(Tile_Mode==T_INVERT  ) Pen_Invert  (0,0);
     if(Tile_Mode==T_DITHER  ) Pen_Dither  (0,0);
     if(Tile_Mode==T_BLEND   ) Pen_Blend   (0,0);
     if(Tile_Mode==T_ERASE   ) Pen_Erase   (0,0);
     if(Tile_Mode==T_SMEAR   ) Pen_Smear   (0,0);
     if(Tile_Mode==T_XMAP    ) Pen_Xmap    (0,0);
     if(Tile_Mode==T_YMAP    ) Pen_Ymap    (0,0);
     if(Tile_Mode==T_XCOLOR  ) Pen_Xcolor  (0,0);
     if(Tile_Mode==T_YCOLOR  ) Pen_Ycolor  (0,0);
     if(Tile_Mode==T_FFADE   ) Pen_Ffade   (0,0);
     if(Tile_Mode==T_BRIGHTEN) Pen_Brighten(0,0);
     if(Tile_Mode==T_DARKEN  ) Pen_Darken  (0,0);
     if(Tile_Mode==T_ADD     ) Pen_Add     (0,0);
     if(Tile_Mode==T_SUBTRACT) Pen_Sub     (0,0);
     TILE=OFF;
     Draw_Object();
   }
   }
   if((c!=1) && (button[a*2+b][1]==1) && (BUTTON==0)) button[a*2+b][1]=0;
   draw_button=YES;
  }

  if((X>300) && (X<313) && (Y>64) && (Y<95))
  {
   if(((BUTTON==0) && (ob==1)) || (BUTTON==2))
   {
    Draw_Mode-=Ds;
    Ds--; if(Ds<0) Ds=0;
    Draw_Mode+=Ds;
    draw_styles=YES;
   }
  }


  if((X>300) && (X<313) && (Y>=96) && (Y<125))
  {
   if(((BUTTON==0) && (ob==1)) || (BUTTON==2))
   {
    Draw_Mode-=Ds;
    Ds++; if(Ds>18-7) Ds=18-7;
    Draw_Mode+=Ds;
    draw_styles=YES;
   }
  }

  if((X>250) && (X<300) && (Y>=67) && (Y<122))
  {
   if(((BUTTON==0) && (ob==1)) || (BUTTON==2))
   {
    a=(Y-67)/8;
    Draw_Mode=Ds+a;
    draw_styles=YES;
   }
  }





  if((X>300) && (X<313) && (Y>127) && (Y<162))
  {
   if(((BUTTON==0) && (ob==1)) || (BUTTON==2))
   {
    Tile_Mode-=Ts;
    Ts--; if(Ts<0) Ts=0;
    Tile_Mode+=Ts;
    draw_tstyles=YES;
   }
  }


  if((X>300) && (X<313) && (Y>=162) && (Y<196))
  {
   if(((BUTTON==0) && (ob==1)) || (BUTTON==2))
   {
    Tile_Mode-=Ts;
    Ts++; if(Ts>17-7) Ts=17-7;
    Tile_Mode+=Ts;
    draw_tstyles=YES;
   }
  }

  if((X>250) && (X<300) && (Y>=127+10) && (Y<127+5+7*8))
  {
   if(((BUTTON==0) && (ob==1)) || (BUTTON==2))
   {
    a=(Y-127-3)/9;
    Tile_Mode=Ts+a;
    draw_tstyles=YES;
   }
  }

  if(draw_styles==YES)
  {
   Box(247,64,300,125,scn,46,"",BLEND);
   Box(300,64,313,94,scn,46,"*",BLEND);
   Box(300,95,313,125,scn,46,"@",BLEND);
   for(i=67;i<122;i++)
   movedata(FP_SEG(lib),FP_OFF(lib)+1024*62,
            FP_SEG(scn),FP_OFF(scn)+250+i*320,49);
   Box(250,64+3+(Draw_Mode-Ds)*8,300,
       64+11+(Draw_Mode-Ds)*8,scn,46,"",BLEND);
   for(a=0;a<7;a++)
   Text_Small(251,64+4+a*8,styles[a+Ds],BLEND,scn);
   draw_styles=NO;
  }


  if(draw_tstyles==YES)
  {
   Box(247,127,300,196,scn,46,"",BLEND);
   Box(300,130,313,162,scn,46,"*",BLEND);
   Box(300,163,313,193,scn,46,"@",BLEND);
   for(i=130;i<193;i++)
   movedata(FP_SEG(lib),FP_OFF(lib)+1024*62,
            FP_SEG(scn),FP_OFF(scn)+250+i*320,49);
   Box(250,127+3+(Tile_Mode-Ts)*9,300,
       127+3+9+(Tile_Mode-Ts)*9,scn,46,"",BLEND);
   for(a=0;a<7;a++)
   Text_Small(251,127+3+a*9,tstyles[a+Ts],BLEND,scn);
   draw_tstyles=NO;
  }


  if(draw_button==YES)
  {
   for(a=0;a<2;a++)
   for(b=0;b<2;b++)
   {
    c=button[a*2+b][0];
    for(i=0;i<32;i++)
    movedata(FP_SEG(lib),FP_OFF(lib)+1024*42+i*32+c*1024,
             FP_SEG(scn),FP_OFF(scn)+180+a*32+(63+b*32)*320+i*320,32);
    c=0;
    if((a==0) && (b==0)) if(WRAP==ON) c=16; else c=0;
    if((a==1) && (b==0)) c=16*32+16;
    if((a==1) && (b==1)) c=16*32;
    for(i=0;i<16;i++)
    movedata(FP_SEG(lib),FP_OFF(lib)+1024*10+i*32+c,
             FP_SEG(scn),FP_OFF(scn)+180+a*32+0xA08+(63+b*32)*320+i*320,16);
   }
   draw_button=NO;
  }

  if(size!=osize)
  {
   Box(220,127,240,196,scn,46,"",BLEND);
   for(i=130;i<193;i++)
   movedata(FP_SEG(lib),FP_OFF(lib)+1024*62,
            FP_SEG(scn),FP_OFF(scn)+223+i*320,14);
   Box(224,131+size*13-13,236,127+size*13,scn,52,"",BLEND);
   Text_Small(224,131+12*0+1,"1x",BLEND,scn);
   Text_Small(224,131+12*1+2,"2x",BLEND,scn);
   Text_Small(224,131+12*2+3,"3x",BLEND,scn);
   Text_Small(224,131+12*3+4,"4x",BLEND,scn);
   Text_Small(224,131+12*4+5,"5x",BLEND,scn);
  }

  if((X>183) && (X<214) && (Y>132) && (Y<190) && (BUTTON==1) && (ob!=1))
  pentype=(Y-130)/15+((X-182)/16)*4;
  if((X>183) && (X<214) && (Y>132) && (Y<190) && (BUTTON==2))
  pentype=(Y-130)/15+((X-182)/16)*4;



  if(pentype!=o_pen)
  {
   Box(180,127,217,196,scn,46,"",BLEND);
   for(i=130;i<193;i++)
   movedata(FP_SEG(lib),FP_OFF(lib)+1024*62,
            FP_SEG(scn),FP_OFF(scn)+183+i*320,31);

   if(pentype<4)
    Box(184,132+pentype*15,199,145+pentype*15,scn,46,"",BLEND);
   else
    Box(198,132+(pentype-4)*15,213,145+(pentype-4)*15,scn,46,"",BLEND);

   Set_Pen(0); Draw_Pen(INVERT,189,130+0*15+4,scn);
   Set_Pen(1); Draw_Pen(INVERT,189,130+1*15+4,scn);
   Set_Pen(2); Draw_Pen(INVERT,189,130+2*15+4,scn);
   Set_Pen(3); Draw_Pen(INVERT,189,130+3*15+4,scn);
   Set_Pen(4); Draw_Pen(INVERT,203,130+0*15+4,scn);
   Set_Pen(5); Draw_Pen(INVERT,203,130+1*15+4,scn);
   Set_Pen(6); Draw_Pen(INVERT,203,130+2*15+4,scn);
   Set_Pen(7); Draw_Pen(INVERT,203,130+3*15+4,scn);
  }
   Set_Pen(pentype);

  if((oObj!=Obj) || (osize!=size)) Draw_Object();


  movedata(FP_SEG(scn  ),FP_OFF(scn  ),
           FP_SEG(scrap),FP_OFF(scrap),0xFA00);

  if(drawpen==YES)
  {
   a=(X-(90 -size*16))/size;
   b=(Y-(100-size*16))/size;
   if(BUTTON!=0)
   {
    if(Draw_Mode==DRAW    ) Pen_Draw    (a,b);
    if(Draw_Mode==BRUSH   ) Pen_Brush   (a,b);
    if(Draw_Mode==X_BRUSH ) Pen_X_Brush (a,b);
    if(Draw_Mode==PAINT   ) Pen_Paint   (a,b);
    if(Draw_Mode==ERASE   ) Pen_Erase   (a,b);
    if(Draw_Mode==INVERT  ) Pen_Invert  (a,b);
    if(Draw_Mode==DITHER  ) Pen_Dither  (a,b);
    if(Draw_Mode==BLEND   ) Pen_Blend   (a,b);
    if(Draw_Mode==SMEAR   ) Pen_Smear   (a,b);
    if(Draw_Mode==XMAP    ) Pen_Xmap    (a,b);
    if(Draw_Mode==YMAP    ) Pen_Ymap    (a,b);
    if(Draw_Mode==XCOLOR  ) Pen_Xcolor  (a,b);
    if(Draw_Mode==YCOLOR  ) Pen_Ycolor  (a,b);
    if(Draw_Mode==FFADE   ) Pen_Ffade   (a,b);
    if(Draw_Mode==BRIGHTEN) Pen_Brighten(a,b);
    if(Draw_Mode==DARKEN  ) Pen_Darken  (a,b);
    if(Draw_Mode==ADD     ) Pen_Add     (a,b);
    if(Draw_Mode==SUBTRACT) Pen_Sub     (a,b);
    for(c=0;c<9;c++) for(d=0;d<9;d++) if(pen[c*9+d]==2) { e=c; f=d; }
    for(c=0;c<9;c++)
    for(d=0;d<9;d++)
    {
      if(pen[c*9+d]==0) continue;
      j=b+c-e;
      k=a+d-f;
      if(WRAP==OFF)
      {
       if(j<0 ) continue;
       if(k<0 ) continue;
       if(j>31) continue;
       if(k>31) continue;
      }
      if(WRAP==ON)
      {
       if(j<0 ) j+=32;
       if(k<0 ) k+=32;
       if(j>31) j-=32;
       if(k>31) k-=32;
      }
      c1=peekb(FP_SEG(clip),FP_OFF(clip)+k+j*32);
      for(g=0;g<size;g++)
      for(h=0;h<size;h++)
      pokeb(FP_SEG(scrap),FP_OFF(scrap)+
       90 -size*16+h+k*size+          //X
      (100-size*16+g+j*size)*320,c1); //Y
    }
    for(h=127;h<196;h++)
    movedata(FP_SEG(scn  ),FP_OFF(scn  )+h*320+243,
             FP_SEG(scrap),FP_OFF(scrap)+h*320+243,70);
   }
   for(c=0;c<9;c++) for(d=0;d<9;d++) if(pen[c*9+d]==2) { e=c; f=d; }
   for(c=0;c<9;c++)
   for(d=0;d<9;d++)
   {
    if(pen[c*9+d]==0) continue;
    j=b+c-e;
    k=a+d-f;
    if(WRAP==OFF)
    {
     if(j<0 ) continue;
     if(k<0 ) continue;
     if(j>31) continue;
     if(k>31) continue;
    }
    if(WRAP==ON)
    {
     if(j<0 ) j+=32;
     if(k<0 ) k+=32;
     if(j>31) j-=32;
     if(k>31) k-=32;
    }
    i=0;
    if((c==e) && (d==f)) i=32*2;
    for(g=0;g<size;g++)
    for(h=0;h<size;h++)
    if((g>0) && (g<size-1) && (h>0) && (h<size-1)) continue; else
    pokeb(FP_SEG(scn),FP_OFF(scn)+
    (90-size*16)+(100-size*16)*320 +
    k*size+g+(j*size+h)*320,32*7-1+i-g-h);
   }
  }


  oObj=Obj,osize=size,o_pen=pentype,start=NO;

  for(i=44;i<63;i++)
  movedata(FP_SEG(menu),FP_OFF(menu)+180+i*320,
           FP_SEG(scn ),FP_OFF(scn )+180+i*320,132);



  if((X>180) && (X<200) && (Y>44) && (Y<62))
  {
   if(BUTTON==0) Box(180,44,200,62,scn,45,"$",NORMAL);
   if(BUTTON==1) Box(180,44,200,62,scn,45,"$",BLEND );
   if(BUTTON==2) Box(180,44,200,62,scn,45,"$",BLEND );
   movedata(FP_SEG(clip),FP_OFF(clip),
            FP_SEG(data),FP_OFF(data)+Obj*1024,1024);
   if(BUTTON==2) Obj--;
   if((BUTTON==1) && (ob!=1)) Obj--;
   if(Obj<0) Obj=0;
   movedata(FP_SEG(data),FP_OFF(data)+Obj*1024,
            FP_SEG(clip),FP_OFF(clip),1024);
  }

  if((X>292) && (X<312) && (Y>44) && (Y<62))
  {
   if(BUTTON==0) Box(292,44,312,62,scn,45,"^",NORMAL);
   if(BUTTON==1) Box(292,44,312,62,scn,45,"^",BLEND);
   if(BUTTON==2) Box(292,44,312,62,scn,45,"^",BLEND);
   movedata(FP_SEG(clip),FP_OFF(clip),
            FP_SEG(data),FP_OFF(data)+Obj*1024,1024);
    if(BUTTON==2) Obj++;
   if((BUTTON==1) && (ob!=1)) Obj++;
   if(Obj>62) Obj=62;
   movedata(FP_SEG(data),FP_OFF(data)+Obj*1024,
            FP_SEG(clip),FP_OFF(clip),1024);
  }

  if((X<20) && (Y<10))
  {
    drawmouse=NO;
    for(i=0;i<32;i++)
    movedata(FP_SEG(lib),FP_OFF(lib)+1024*47+i*32,
             FP_SEG(scn),FP_OFF(scn)+i*320,32);
  }
  else
  if((X<20) && (Y>190))
  {
    drawmouse=NO;
    for(i=0;i<32;i++)
    movedata(FP_SEG(lib),FP_OFF(lib)+1024*47+i*32,
             FP_SEG(scn),FP_OFF(scn)+(168+i)*320,32);
  }
  if((X>300) && (Y>190))
  {
   drawmouse=NO;
   Quad();
  }

  if((((X<20) && (Y<10 )) ||
      ((X<20) && (Y>190))) && (ob==0) && (BUTTON==1)) exit=YES;


  Time();
  Draw_Mouse();
  movedata(FP_SEG(scrap),FP_OFF(scrap),
           FP_SEG(scn  ),FP_OFF(scn  ),0xFA00);
  drawmouse=YES;
  }
 drawmouse=YES; osize=9;
}

void Draw_Object(void)
{
 static int a,b,i;
 static unsigned char c;
  for(i=0;i<200;i++)
  movedata(FP_SEG(menu),FP_OFF(menu)+i*320,
           FP_SEG(scn ),FP_OFF(scn )+i*320,173);
 Box(87-size*16,97-size*16,93+size*16,103+size*16,scn,46,"",SMALL);

 if(size==1)
  for(i=0;i<32;i++)
  movedata(FP_SEG(clip),FP_OFF(clip)+i*32,
           FP_SEG(scn ),FP_OFF(scn )+74+84*320+i*320,32);
 if(size==2)
 for(a=0;a<32;a++)
 for(b=0;b<32;b++)
 {
  c=peekb(FP_SEG(clip),FP_OFF(clip)+a+b*32);
  poke(FP_SEG(scn),FP_OFF(scn)+a*2+b*640+68*320+58,c*0x100+c);
  poke(FP_SEG(scn),FP_OFF(scn)+a*2+b*640+69*320+58,c*0x100+c);
 }

 if(size==3)
 for(a=0;a<32;a++)
 for(b=0;b<32;b++)
 {
  c=peekb(FP_SEG(clip),FP_OFF(clip)+a+b*32);
  poke(FP_SEG(scn),FP_OFF(scn)+a*3+b*320*3+52*320+42,c*0x100+c);
  poke(FP_SEG(scn),FP_OFF(scn)+a*3+b*320*3+53*320+42,c*0x100+c);
  poke(FP_SEG(scn),FP_OFF(scn)+a*3+b*320*3+54*320+42,c*0x100+c);

  pokeb(FP_SEG(scn),FP_OFF(scn)+a*3+b*320*3+52*320+44,c);
  pokeb(FP_SEG(scn),FP_OFF(scn)+a*3+b*320*3+53*320+44,c);
  pokeb(FP_SEG(scn),FP_OFF(scn)+a*3+b*320*3+54*320+44,c);
 }

 if(size==4)
 for(a=0;a<32;a++)
 for(b=0;b<32;b++)
 {
  c=peekb(FP_SEG(clip),FP_OFF(clip)+a+b*32);
  poke(FP_SEG(scn),FP_OFF(scn)+a*4+b*320*4+36*320+26,c*0x100+c);
  poke(FP_SEG(scn),FP_OFF(scn)+a*4+b*320*4+37*320+26,c*0x100+c);
  poke(FP_SEG(scn),FP_OFF(scn)+a*4+b*320*4+38*320+26,c*0x100+c);
  poke(FP_SEG(scn),FP_OFF(scn)+a*4+b*320*4+39*320+26,c*0x100+c);

  poke(FP_SEG(scn),FP_OFF(scn)+a*4+b*320*4+36*320+28,c*0x100+c);
  poke(FP_SEG(scn),FP_OFF(scn)+a*4+b*320*4+37*320+28,c*0x100+c);
  poke(FP_SEG(scn),FP_OFF(scn)+a*4+b*320*4+38*320+28,c*0x100+c);
  poke(FP_SEG(scn),FP_OFF(scn)+a*4+b*320*4+39*320+28,c*0x100+c);
 }


 if(size==5)
 for(a=0;a<32;a++)
 for(b=0;b<32;b++)
 {
  c=peekb(FP_SEG(clip),FP_OFF(clip)+a+b*32);
  poke(FP_SEG(scn),FP_OFF(scn)+a*5+b*320*5+20*320+10,c*0x100+c);
  poke(FP_SEG(scn),FP_OFF(scn)+a*5+b*320*5+21*320+10,c*0x100+c);
  poke(FP_SEG(scn),FP_OFF(scn)+a*5+b*320*5+22*320+10,c*0x100+c);
  poke(FP_SEG(scn),FP_OFF(scn)+a*5+b*320*5+23*320+10,c*0x100+c);
  poke(FP_SEG(scn),FP_OFF(scn)+a*5+b*320*5+24*320+10,c*0x100+c);

  poke(FP_SEG(scn),FP_OFF(scn)+a*5+b*320*5+20*320+12,c*0x100+c);
  poke(FP_SEG(scn),FP_OFF(scn)+a*5+b*320*5+21*320+12,c*0x100+c);
  poke(FP_SEG(scn),FP_OFF(scn)+a*5+b*320*5+22*320+12,c*0x100+c);
  poke(FP_SEG(scn),FP_OFF(scn)+a*5+b*320*5+23*320+12,c*0x100+c);
  poke(FP_SEG(scn),FP_OFF(scn)+a*5+b*320*5+24*320+12,c*0x100+c);

  pokeb(FP_SEG(scn),FP_OFF(scn)+a*5+b*320*5+20*320+14,c);
  pokeb(FP_SEG(scn),FP_OFF(scn)+a*5+b*320*5+21*320+14,c);
  pokeb(FP_SEG(scn),FP_OFF(scn)+a*5+b*320*5+22*320+14,c);
  pokeb(FP_SEG(scn),FP_OFF(scn)+a*5+b*320*5+23*320+14,c);
  pokeb(FP_SEG(scn),FP_OFF(scn)+a*5+b*320*5+24*320+14,c);
 }

 char txt[15];
 sprintf(txt,"Tile %d of 62",Obj);
 Box(202,44,290,62,menu,46,txt,SMALLBLEND);
}

void Quad(void)
{
 int i;
 for(i=0;i<32;i++)
  movedata(FP_SEG(clip),FP_OFF(clip)+i*32,
           FP_SEG(scn ),FP_OFF(scn )+246+130*320+i*320,32);
 for(i=0;i<32;i++)
  movedata(FP_SEG(clip),FP_OFF(clip)+i*32,
           FP_SEG(scn ),FP_OFF(scn )+246+162*320+i*320,32);
 for(i=0;i<32;i++)
  movedata(FP_SEG(clip),FP_OFF(clip)+i*32,
           FP_SEG(scn ),FP_OFF(scn )+278+130*320+i*320,32);
 for(i=0;i<32;i++)
  movedata(FP_SEG(clip),FP_OFF(clip)+i*32,
           FP_SEG(scn ),FP_OFF(scn )+278+162*320+i*320,32);
}

void Time(void)
{
 char txt[16];
 struct  time t;
 gettime(&t);
 if(t.ti_hour>12) t.ti_hour-=12;
 sprintf(txt,"%2d:%02d:%02d.%02d",
         t.ti_hour, t.ti_min, t.ti_sec, t.ti_hund);
 Text_Small(49,185,txt,BLEND,scn);
}

void Set_Pen(int type)
{
 int a;
 if(type==0)
 {
  char b[81]={ 0,0,0,0,0,0,0,0,0,
               0,0,0,0,0,0,0,0,0,
               0,0,0,0,0,0,0,0,0,
               0,0,0,0,0,0,0,0,0,
               0,0,0,0,2,0,0,0,0,
               0,0,0,0,0,0,0,0,0,
               0,0,0,0,0,0,0,0,0,
               0,0,0,0,0,0,0,0,0,
               0,0,0,0,0,0,0,0,0, };
  for(a=0;a<81;a++) pen[a]=b[a];
 }
 if(type==1)
 {
  char b[81]={ 0,0,0,0,0,0,0,0,0,
               0,0,0,0,0,0,0,0,0,
               0,0,1,1,1,1,1,0,0,
               0,0,1,1,1,1,1,0,0,
               0,0,1,1,2,1,1,0,0,
               0,0,1,1,1,1,1,0,0,
               0,0,1,1,1,1,1,0,0,
               0,0,0,0,0,0,0,0,0,
               0,0,0,0,0,0,0,0,0, };
  for(a=0;a<81;a++) pen[a]=b[a];
 }
 if(type==2)
 {
  char b[81]={ 1,1,1,1,1,1,1,1,1,
               1,1,1,1,1,1,1,1,1,
               1,1,1,1,1,1,1,1,1,
               1,1,1,1,1,1,1,1,1,
               1,1,1,1,2,1,1,1,1,
               1,1,1,1,1,1,1,1,1,
               1,1,1,1,1,1,1,1,1,
               1,1,1,1,1,1,1,1,1,
               1,1,1,1,1,1,1,1,1, };
  for(a=0;a<81;a++) pen[a]=b[a];
 }
 if(type==3)
 {
  char b[81]={ 0,0,0,0,1,0,0,0,0,
               0,0,0,1,1,1,0,0,0,
               0,0,1,1,1,1,1,0,0,
               0,1,1,1,1,1,1,1,0,
               1,1,1,1,2,1,1,1,1,
               0,1,1,1,1,1,1,1,0,
               0,0,1,1,1,1,1,0,0,
               0,0,0,1,1,1,0,0,0,
               0,0,0,0,1,0,0,0,0, };
  for(a=0;a<81;a++) pen[a]=b[a];
 }
 if(type==4)
 {
  char b[81]={ 0,0,0,0,0,0,0,0,0,
               0,0,0,0,0,0,0,0,0,
               0,0,0,0,0,0,0,0,0,
               0,0,0,1,1,1,0,0,0,
               0,0,1,1,2,1,1,0,0,
               0,0,1,1,1,1,1,0,0,
               0,0,0,1,1,1,0,0,0,
               0,0,0,0,0,0,0,0,0,
               0,0,0,0,0,0,0,0,0, };
  for(a=0;a<81;a++) pen[a]=b[a];
 }
 if(type==5)
 {
  char b[81]={ 0,0,0,1,1,1,0,0,0,
               0,1,1,1,1,1,1,1,0,
               0,1,1,1,1,1,1,1,0,
               1,1,1,1,1,1,1,1,1,
               1,1,1,1,2,1,1,1,1,
               1,1,1,1,1,1,1,1,1,
               0,1,1,1,1,1,1,1,0,
               0,1,1,1,1,1,1,1,0,
               0,0,0,1,1,1,0,0,0, };
  for(a=0;a<81;a++) pen[a]=b[a];
 }
 if(type==6)
 {
  char b[81]={ 1,1,0,0,0,0,0,1,1,
               1,1,1,0,0,0,1,1,1,
               0,1,1,1,0,1,1,1,0,
               0,0,1,1,1,1,1,0,0,
               0,0,0,1,2,1,0,0,0,
               0,0,1,1,1,1,1,0,0,
               0,1,1,1,0,1,1,1,0,
               1,1,1,0,0,0,1,1,1,
               1,1,0,0,0,0,0,1,1, };
  for(a=0;a<81;a++) pen[a]=b[a];
 }
 if(type==7)
 {
  char b[81];
  for(a=0;a<81;a++) if(random(10)==1) b[a]=1; else b[a]=0;
  for(a=0;a<81;a++) pen[a]=b[a];
  pen[40]=2;
 }
}

void Draw_Pen(int mode,int x,int y,void *buf)
{
 int a,b,midx,midy;
 unsigned char c,d;
 for(a=0;a<81;a++) if(pen[a]==2) midx=2;
 midy=midx/9;
 midx=midx-midy*9;

 for(a=0;a<9;a++)
 for(b=0;b<9;b++)
 {
  if(pen[a*9+b]!=0)
  {
   if(mode==INVERT)
   {
    c=peekb(FP_SEG(buf),FP_OFF(buf)+x+y*320+a*320+b-midx-midy*320);
    d=c/32; c=c-d*32;
      pokeb(FP_SEG(buf),FP_OFF(buf)+x+y*320+a*320+b-midx-midy*320,d*32+32-c);
   }
  }
 }
}

void Pen_Draw(int x,int y)
{
 int a,b,c,d,X,Y,t=9;
 int c1;
 if(BUTTON==1) c1=color1;
 if(BUTTON==2) c1=color2;
 for(c=0;c<9;c++) for(d=0;d<9;d++) if(pen[c*9+d]==2) { a=c; b=d; }
 if(TILE==ON) { a=0,b=0,t=32,c1=color1; }
 for(c=0;c<t;c++)
 for(d=0;d<t;d++)
 {
  if((TILE!=ON) && (pen[c*9+d]==0)) continue;
  X=x+d-b;
  Y=y+c-a;
  if(WRAP==ON)
  {
   if(X<0) X+=32;
   if(Y<0) Y+=32;
   if(X>31) X-=32;
   if(Y>31) Y-=32;
  }
  if(WRAP==OFF)
   if((X<0) || (Y<0) || (Y>31) || (X>31)) continue;
  pokeb(FP_SEG(clip),FP_OFF(clip)+X+Y*32,c1);
 }
}

void Pen_Brush(int x,int y)
{
 int a,b,c,d,f,g,h,i,X,Y;
 int c1;
 if(BUTTON==1) c1=color1;
 if(BUTTON==2) c1=color2;
 i=5;
 if(pentype==1) i=3;
 if(pentype==4) i=3;
 g=c1%32; h=c1/32;
 unsigned char e;
 for(c=0;c<9;c++) for(d=0;d<9;d++) if(pen[c*9+d]==2) { a=c; b=d; }
 for(c=0;c<9;c++)
 for(d=0;d<9;d++)
 {
  if(pen[c*9+d]==0) continue;
  X=x+d-b;
  Y=y+c-a;
  if(WRAP==ON)
  {
   if(X<0) X+=32;
   if(Y<0) Y+=32;
   if(X>31) X-=32;
   if(Y>31) Y-=32;
  }
  if(WRAP==OFF)
   if((X<0) || (Y<0) || (Y>31) || (X>31)) continue;
  e=peekb(FP_SEG(clip),FP_OFF(clip)+X+Y*32);
  e%=32;
  f=(int)sqrtl((c-a)*(c-a)+(d-b)*(d-b));
  f=(e*f*3+g*(i-f))/(f*3+(i-f));
  if(f>31) f=31; if(f<0) f=0;
  pokeb(FP_SEG(clip),FP_OFF(clip)+X+Y*32,f+h*32);
 }
}

void Pen_Paint(int x,int y)
{
 Pen_Draw(x,y);
 Pen_Dither(x,y);
 Pen_Dither(x,y);
 Pen_Blend(x,y);
}

void Pen_Invert(int x,int y)
{
 int a,b,c,d,l,X,Y,t=9;
 unsigned char c1;
 for(c=0;c<9;c++) for(d=0;d<9;d++) if(pen[c*9+d]==2) { a=c; b=d; }
 if(TILE==ON) { a=0,b=0,t=32; }
 for(c=0;c<t;c++)
 for(d=0;d<t;d++)
 {
  if((TILE!=ON) && (pen[c*9+d]==0)) continue;
  X=x+d-b;
  Y=y+c-a;
  if(WRAP==ON)
  {
   if(X<0) X+=32;
   if(Y<0) Y+=32;
   if(X>31) X-=32;
   if(Y>31) Y-=32;
  }
  if(WRAP==OFF)
   if((X<0) || (Y<0) || (Y>31) || (X>31)) continue;
  c1=peekb(FP_SEG(clip),FP_OFF(clip)+X+Y*32);
  l=c1/32;
  c1=31-(c1-l*32)+l*32;
  pokeb(FP_SEG(clip),FP_OFF(clip)+X+Y*32,c1);
 }
}

void Pen_Dither(int x,int y)
{
 int a,b,c,d,e,l,X,Y,t=9;
 unsigned char c1;
 for(c=0;c<9;c++) for(d=0;d<9;d++) if(pen[c*9+d]==2) { a=c; b=d; }
 if(TILE==ON) { a=0,b=0,t=32; }
 for(c=0;c<t;c++)
 for(d=0;d<t;d++)
 {
  if((TILE!=ON) && (pen[c*9+d]==0)) continue;
  X=x+d-b;
  Y=y+c-a;
  if(WRAP==ON)
  {
   if(X<0) X+=32;
   if(Y<0) Y+=32;
   if(X>31) X-=32;
   if(Y>31) Y-=32;
  }
  if(WRAP==OFF)
   if((X<0) || (Y<0) || (Y>31) || (X>31)) continue;
  c1=peekb(FP_SEG(clip),FP_OFF(clip)+X+Y*32);
  l=c1/32;
  e=c1-l*32;
  e+=random(3)-1;
  if(e>31) e=31;
  if(e<0)  e=0;
  pokeb(FP_SEG(clip),FP_OFF(clip)+X+Y*32,e+l*32);
 }
}

void Pen_Blend(int x,int y)
{
 int a,b,c,d,e,f,l,grid[6],dat[7],t=9;
 unsigned char g,h,i,j,k;
 movedata(FP_SEG(clip ),FP_OFF(clip ),
          FP_SEG(scrap),FP_OFF(scrap),1024);
 for(c=0;c<9;c++) for(d=0;d<9;d++) if(pen[c*9+d]==2) { a=c; b=d; }
 if(TILE==ON) { a=0,b=0,t=32; }
 for(c=0;c<t;c++)
 for(d=0;d<t;d++)
 {
  if((TILE!=ON) && (pen[c*9+d]==0)) continue;
  grid[0]=x+d-b;
  grid[1]=x+d-b+1;
  grid[2]=x+d-b-1;
  grid[3]=y+c-a;
  grid[4]=y+c-a+1;
  grid[5]=y+c-a-1;

  if(WRAP==ON)
  for(l=0;l<6;l++)
  {
   if(grid[l]>31) grid[l]-=32;
   if(grid[l]<0 ) grid[l]+=32;
  }
  if(WRAP==OFF)
  for(l=0;l<6;l++)
  {
   if(grid[l]>31) grid[l]=93;
   if(grid[l]<0 ) grid[l]=93;
  }
  if((grid[0]!=93) && (grid[3]!=93))
  {
   g=peekb(FP_SEG(scrap),FP_OFF(scrap)+grid[0]+grid[3]*32);
   dat[4]=g-(g/32)*32;
  } else dat[4]=0;
  if((grid[0]!=93) && (grid[4]!=93))
  {
   h=peekb(FP_SEG(scrap),FP_OFF(scrap)+grid[0]+grid[4]*32);
   dat[0]=h-(h/32)*32;
  } else dat[0]=0;
  if((grid[0]!=93) && (grid[5]!=93))
  {
   i=peekb(FP_SEG(scrap),FP_OFF(scrap)+grid[0]+grid[5]*32);
   dat[1]=i-(i/32)*32;
  } else dat[1]=0;
  if((grid[1]!=93) && (grid[3]!=93))
  {
   j=peekb(FP_SEG(scrap),FP_OFF(scrap)+grid[1]+grid[3]*32);
   dat[2]=j-(j/32)*32;
  } else dat[2]=0;
  if((grid[2]!=93) && (grid[3]!=93))
  {
   k=peekb(FP_SEG(scrap),FP_OFF(scrap)+grid[2]+grid[3]*32);
   dat[3]=k-(k/32)*32;
  } else dat[3]=0;
  i=4;
  for(h=0;h<4;h++) if(dat[h]==0) i--;
  e=g/32;
  if(i!=0)
  f=((dat[0]+dat[1]+dat[2]+dat[3])/i+dat[4])/2;
  if(f<0) f=0;
  if(f>31) f=31;
  if((grid[0]!=93) && (grid[3]!=93))
  pokeb(FP_SEG(clip),FP_OFF(clip)+grid[0]+grid[3]*32,e*32+f);
 }
  movedata(FP_SEG(scn  ),FP_OFF(scn  ),
           FP_SEG(scrap),FP_OFF(scrap),0xFA00);
}

void Pen_Ycolor(int x,int y)
{
 int a,b,c,d,e,l,X,Y,t=9;
 unsigned char c1;
 e=color2;
 if(BUTTON==1) e=color1;
 for(c=0;c<9;c++) for(d=0;d<9;d++) if(pen[c*9+d]==2) { a=c; b=d; }
 if(TILE==ON) { a=0,b=0,t=32,e=color1; }
 for(c=0;c<t;c++)
 for(d=0;d<t;d++)
 {
  if((TILE!=ON) && (pen[c*9+d]==0)) continue;
  X=x+d-b;
  Y=y+c-a;
  if(WRAP==ON)
  {
   if(X<0) X+=32;
   if(Y<0) Y+=32;
   if(X>31) X-=32;
   if(Y>31) Y-=32;
  }
  if(WRAP==OFF)
   if((X<0) || (Y<0) || (Y>31) || (X>31)) continue;
  c1=peekb(FP_SEG(clip),FP_OFF(clip)+X+Y*32);
  l=c1/32;
  c1=e%32;
  pokeb(FP_SEG(clip),FP_OFF(clip)+X+Y*32,c1+l*32);
 }
}

void Pen_Xcolor(int x,int y)
{
 int a,b,c,d,e,l,X,Y,t=9;
 unsigned char c1;
 e=color2;
 if(BUTTON==1) e=color1;
 for(c=0;c<9;c++) for(d=0;d<9;d++) if(pen[c*9+d]==2) { a=c; b=d; }
 if(TILE==ON) { a=0,b=0,t=32,e=color1; }
 for(c=0;c<t;c++)
 for(d=0;d<t;d++)
 {
  if((TILE!=ON) && (pen[c*9+d]==0)) continue;
  X=x+d-b;
  Y=y+c-a;
  if(WRAP==ON)
  {
   if(X<0) X+=32;
   if(Y<0) Y+=32;
   if(X>31) X-=32;
   if(Y>31) Y-=32;
  }
  if(WRAP==OFF)
   if((X<0) || (Y<0) || (Y>31) || (X>31)) continue;
  c1=peekb(FP_SEG(clip),FP_OFF(clip)+X+Y*32);
  l=e/32;
  c1%=32;
  pokeb(FP_SEG(clip),FP_OFF(clip)+X+Y*32,c1+l*32);
 }
}

void Pen_Smear(int x,int y)
{
 int a,b,c,d,e,f,l,grid[6],dat[7],t=9;
 unsigned char g,h,i,j,k;
 movedata(FP_SEG(clip ),FP_OFF(clip ),
          FP_SEG(scrap),FP_OFF(scrap),1024);
 for(c=0;c<9;c++) for(d=0;d<9;d++) if(pen[c*9+d]==2) { a=c; b=d; }
 if(TILE==ON) { a=0,b=0,t=32; }
 for(c=0;c<t;c++)
 for(d=0;d<t;d++)
 {
  if((TILE!=ON) && (pen[c*9+d]==0)) continue;
  grid[0]=x+d-b;
  grid[1]=x+d-b+1;
  grid[2]=x+d-b-1;
  grid[3]=y+c-a;
  grid[4]=y+c-a+1;
  grid[5]=y+c-a-1;

  if(WRAP==ON)
  for(l=0;l<6;l++)
  {
   if(grid[l]>31) grid[l]-=32;
   if(grid[l]<0 ) grid[l]+=32;
  }
  if(WRAP==OFF)
  for(l=0;l<6;l++)
  {
   if(grid[l]>31) grid[l]=93;
   if(grid[l]<0 ) grid[l]=93;
  }
  if((grid[0]!=93) && (grid[3]!=93))
  {
   g=peekb(FP_SEG(scrap),FP_OFF(scrap)+grid[0]+grid[3]*32);
   dat[4]=g-(g/32)*32;
  } else dat[4]=0;
  if((grid[0]!=93) && (grid[4]!=93))
  {
   h=peekb(FP_SEG(scrap),FP_OFF(scrap)+grid[0]+grid[4]*32);
   dat[0]=h-(h/32)*32;
  } else dat[0]=0;
  if((grid[0]!=93) && (grid[5]!=93))
  {
   i=peekb(FP_SEG(scrap),FP_OFF(scrap)+grid[0]+grid[5]*32);
   dat[1]=i-(i/32)*32;
  } else dat[1]=0;
  if((grid[1]!=93) && (grid[3]!=93))
  {
   j=peekb(FP_SEG(scrap),FP_OFF(scrap)+grid[1]+grid[3]*32);
   dat[2]=j-(j/32)*32;
  } else dat[2]=0;
  if((grid[2]!=93) && (grid[3]!=93))
  {
   k=peekb(FP_SEG(scrap),FP_OFF(scrap)+grid[2]+grid[3]*32);
   dat[3]=k-(k/32)*32;
  } else dat[3]=0;
  i=4;
  for(h=0;h<4;h++) if(dat[h]==0) i--;
  e=g/32;
  if(i!=0)
  f=((dat[0]+dat[1]+dat[2]+dat[3])/i+dat[4])/2;
  if(f<0) f=0;
  if(f>31) f=31;
  if((grid[0]!=93) && (grid[3]!=93))
  pokeb(FP_SEG(clip),FP_OFF(clip)+grid[0]+grid[3]*32,e*32+f);
 }
  movedata(FP_SEG(scn  ),FP_OFF(scn  ),
           FP_SEG(scrap),FP_OFF(scrap),0xFA00);
}

void Pen_Ymap(int x,int y)
{
 int a,b,c,d,l,X,Y,t=9;
 unsigned char c1;
 for(c=0;c<9;c++) for(d=0;d<9;d++) if(pen[c*9+d]==2) { a=c; b=d; }
 if(TILE==ON) { a=0,b=0,t=32; }
 for(c=0;c<t;c++)
 for(d=0;d<t;d++)
 {
  if((TILE!=ON) && (pen[c*9+d]==0)) continue;
  X=x+d-b;
  Y=y+c-a;
  if(WRAP==ON)
  {
   if(X<0) X+=32;
   if(Y<0) Y+=32;
   if(X>31) X-=32;
   if(Y>31) Y-=32;
  }
  if(WRAP==OFF)
   if((X<0) || (Y<0) || (Y>31) || (X>31)) continue;
  c1=peekb(FP_SEG(clip),FP_OFF(clip)+X+Y*32);
  l=c1/32;
  c1=peekb(FP_SEG(clip),FP_OFF(clip)+1024*3+X+Y*32);
  c1%=32;
  pokeb(FP_SEG(clip),FP_OFF(clip)+X+Y*32,c1+l*32);
 }
}

void Pen_Xmap(int x,int y)
{
 int a,b,c,d,l,X,Y,t=9;
 unsigned char c1;
 for(c=0;c<9;c++) for(d=0;d<9;d++) if(pen[c*9+d]==2) { a=c; b=d; }
 if(TILE==ON) { a=0,b=0,t=32; }
 for(c=0;c<t;c++)
 for(d=0;d<t;d++)
 {
  if((TILE!=ON) && (pen[c*9+d]==0)) continue;
  X=x+d-b;
  Y=y+c-a;
  if(WRAP==ON)
  {
   if(X<0) X+=32;
   if(Y<0) Y+=32;
   if(X>31) X-=32;
   if(Y>31) Y-=32;
  }
  if(WRAP==OFF)
   if((X<0) || (Y<0) || (Y>31) || (X>31)) continue;
  c1=peekb(FP_SEG(clip),FP_OFF(clip)+1024*3+X+Y*32);
  l=c1/32;
  c1=peekb(FP_SEG(clip),FP_OFF(clip)+X+Y*32);
  c1%=32;
  pokeb(FP_SEG(clip),FP_OFF(clip)+X+Y*32,c1+l*32);
 }
}

void Pen_Ffade(int x,int y)
{
 Pen_Dither(x,y);
 Pen_Dither(x,y);
 Pen_Blend(x,y);
}

void Pen_X_Brush(int x,int y)
{
 int a,b,c,d,f,g,h,i,X,Y,t=9;
 unsigned char e;
 unsigned char c1;
 i=5;
 if(pentype==1) i=3;
 if(pentype==4) i=3;
 for(c=0;c<9;c++) for(d=0;d<9;d++) if(pen[c*9+d]==2) { a=c; b=d; }
 if(TILE==ON) { a=0,b=0,t=32; }
 for(c=0;c<t;c++)
 for(d=0;d<t;d++)
 {
  if((TILE!=ON) && (pen[c*9+d]==0)) continue;
  X=x+d-b;
  Y=y+c-a;
  if(WRAP==ON)
  {
   if(X<0) X+=32;
   if(Y<0) Y+=32;
   if(X>31) X-=32;
   if(Y>31) Y-=32;
  }
  if(WRAP==OFF)
   if((X<0) || (Y<0) || (Y>31) || (X>31)) continue;
  e =peekb(FP_SEG(clip),FP_OFF(clip)+X+Y*32);
  c1=peekb(FP_SEG(clip),FP_OFF(clip)+1024*3+X+Y*32);
  g=c1%32; h=c1/32;
  e%=32;
  f=(int)sqrtl((c-a)*(c-a)+(d-b)*(d-b));
  f=(e*f*3+g*(i-f))/(f*3+(i-f));
  if(f>31) f=31; if(f<0) f=0;
  pokeb(FP_SEG(clip),FP_OFF(clip)+X+Y*32,f+h*32);
 }
}

void Pen_Brighten(int x,int y)
{
 int a,b,c,d,l,X,Y,t=9;
 unsigned char c1;
 for(c=0;c<9;c++) for(d=0;d<9;d++) if(pen[c*9+d]==2) { a=c; b=d; }
 if(TILE==ON) { a=0,b=0,t=32; }
 for(c=0;c<t;c++)
 for(d=0;d<t;d++)
 {
  if((TILE!=ON) && (pen[c*9+d]==0)) continue;
  X=x+d-b;
  Y=y+c-a;
  if(WRAP==ON)
  {
   if(X<0) X+=32;
   if(Y<0) Y+=32;
   if(X>31) X-=32;
   if(Y>31) Y-=32;
  }
  if(WRAP==OFF)
   if((X<0) || (Y<0) || (Y>31) || (X>31)) continue;
  c1=peekb(FP_SEG(clip),FP_OFF(clip)+X+Y*32);
  l=c1/32; c1%=32;
  c1++;
  if(c1>31) c1=31;
  pokeb(FP_SEG(clip),FP_OFF(clip)+X+Y*32,c1+l*32);
 }
}

void Pen_Darken(int x,int y)
{
 int a,b,c,d,e,l,X,Y,t=9;
 unsigned char c1;
 for(c=0;c<9;c++) for(d=0;d<9;d++) if(pen[c*9+d]==2) { a=c; b=d; }
 if(TILE==ON) { a=0,b=0,t=32; }
 for(c=0;c<t;c++)
 for(d=0;d<t;d++)
 {
  if(TILE==ON) { a=0,b=0,t=32; }
  if((TILE!=ON) && (pen[c*9+d]==0)) continue;
  X=x+d-b;
  Y=y+c-a;
  if(WRAP==ON)
  {
   if(X<0) X+=32;
   if(Y<0) Y+=32;
   if(X>31) X-=32;
   if(Y>31) Y-=32;
  }
  if(WRAP==OFF)
   if((X<0) || (Y<0) || (Y>31) || (X>31)) continue;
  c1=peekb(FP_SEG(clip),FP_OFF(clip)+X+Y*32);
  l=c1/32; e=c1%32;
  e--;
  if(e<0) e=0;
  pokeb(FP_SEG(clip),FP_OFF(clip)+X+Y*32,e+l*32);
 }
}

void Pen_Add(int x,int y)
{
 int a,b,c,d,e,l,X,Y,t=9;
 unsigned char c1;
 for(c=0;c<9;c++) for(d=0;d<9;d++) if(pen[c*9+d]==2) { a=c; b=d; }
 if(TILE==ON) { a=0,b=0,t=32; }
 for(c=0;c<t;c++)
 for(d=0;d<t;d++)
 {
  if((TILE!=ON) && (pen[c*9+d]==0)) continue;
  X=x+d-b;
  Y=y+c-a;
  if(WRAP==ON)
  {
   if(X<0) X+=32;
   if(Y<0) Y+=32;
   if(X>31) X-=32;
   if(Y>31) Y-=32;
  }
  if(WRAP==OFF)
   if((X<0) || (Y<0) || (Y>31) || (X>31)) continue;
  c1=peekb(FP_SEG(clip),FP_OFF(clip)+X+Y*32);
  l=c1/32; e=c1%32;
  c1=peekb(FP_SEG(clip),FP_OFF(clip)+1024*3+X+Y*32);
  c1%=32;
  c1=c1+e;
  if(c1>31) c1=31;
  pokeb(FP_SEG(clip),FP_OFF(clip)+X+Y*32,c1+l*32);
 }
}

void Pen_Sub(int x,int y)
{
 int a,b,c,d,e,l,X,Y,t=9;
 unsigned char c1;
 for(c=0;c<9;c++) for(d=0;d<9;d++) if(pen[c*9+d]==2) { a=c; b=d; }
 if(TILE==ON) { a=0,b=0,t=32; }
 for(c=0;c<t;c++)
 for(d=0;d<t;d++)
 {
  if((TILE!=ON) && (pen[c*9+d]==0)) continue;
  X=x+d-b;
  Y=y+c-a;
  if(WRAP==ON)
  {
   if(X<0) X+=32;
   if(Y<0) Y+=32;
   if(X>31) X-=32;
   if(Y>31) Y-=32;
  }
  if(WRAP==OFF)
   if((X<0) || (Y<0) || (Y>31) || (X>31)) continue;
  c1=peekb(FP_SEG(clip),FP_OFF(clip)+X+Y*32);
  l=c1/32; e=c1%32;
  c1=peekb(FP_SEG(clip),FP_OFF(clip)+1024*3+X+Y*32);
  c1%=32;
  e=c1-e;
  if(e<0) e=0;
  pokeb(FP_SEG(clip),FP_OFF(clip)+X+Y*32,e+l*32);
 }
}

void Pen_Erase(int x,int y)
{
 int a,b,c,d,e,l,X,Y,t=9;
 if(BUTTON==1) { e=color1; l=color2; }
 if(BUTTON==2) { l=color1; e=color2; }
 unsigned char c1;
 for(c=0;c<9;c++) for(d=0;d<9;d++) if(pen[c*9+d]==2) { a=c; b=d; }
 if(TILE==ON) { a=0,b=0,t=32,e=color1,l=color2; }
 for(c=0;c<t;c++)
 for(d=0;d<t;d++)
 {
  if(TILE==ON) { a=0,b=0,t=32; }
  if((TILE!=ON) && (pen[c*9+d]==0)) continue;
  X=x+d-b;
  Y=y+c-a;
  if(WRAP==ON)
  {
   if(X<0) X+=32;
   if(Y<0) Y+=32;
   if(X>31) X-=32;
   if(Y>31) Y-=32;
  }
  if(WRAP==OFF)
   if((X<0) || (Y<0) || (Y>31) || (X>31)) continue;
  c1=peekb(FP_SEG(clip),FP_OFF(clip)+X+Y*32);
  if(c1==e) c1=l;
  pokeb(FP_SEG(clip),FP_OFF(clip)+X+Y*32,c1);
 }
}


void Tile_XBlend(int x,int y)
{
 int a,b,c,d,e,X,Y,t=9;
 unsigned char c1,c2;
 for(c=0;c<9;c++) for(d=0;d<9;d++) if(pen[c*9+d]==2) { a=c; b=d; }
 if(TILE==ON) { a=0,b=0,t=32; }
 for(c=0;c<t;c++)
 for(d=0;d<t;d++)
 {
  if((TILE!=ON) && (pen[c*9+d]==0)) continue;
  X=x+d-b;
  Y=y+c-a;
  if(WRAP==ON)
  {
   if(X<0) X+=32;
   if(Y<0) Y+=32;
   if(X>31) X-=32;
   if(Y>31) Y-=32;
  }
  if(WRAP==OFF)
   if((X<0) || (Y<0) || (Y>31) || (X>31)) continue;
  c1=peekb(FP_SEG(clip),FP_OFF(clip)+X+Y*32);
  c2=peekb(FP_SEG(clip),FP_OFF(clip)+1024*3+X+Y*32);

  e=(c1%32+c2%32)/2;
  c1/=32;
  pokeb(FP_SEG(clip),FP_OFF(clip)+X+Y*32,e+c1*32);
 }
}

void Mapping(void)
{
 int exit=NO,start=YES;
 int a,b,c,d,i;
 int ob=0,pos=0,num=0;

 Smear_Out();
 Box(0  ,0  ,256,199,scn,46,"",NORMAL);
 Box(256,0  ,296,199,scn,46,"",NORMAL);
 Box(296,0  ,319,100,scn,46,"*",NORMAL);
 Box(296,100,319,199,scn,46,"@",NORMAL);

 while(exit!=YES)
 {
  ob=BUTTON;
  Mouse_Status();

  if((X>296) && (X<320) && (Y>0  ) && (Y<100) && ((BUTTON==1) && (ob!=1)))
  { pos--; start=YES; if(pos<0) pos=0; }
  if((X>296) && (X<320) && (Y>100) && (Y<200) && ((BUTTON==1) && (ob!=1)))
  { pos++; start=YES; if(pos>56) pos=56; }
  if((X>296) && (X<320) && (Y>0  ) && (Y<100) &&  (BUTTON==2))
  { pos--; start=YES; if(pos<0) pos=0; }
  if((X>296) && (X<320) && (Y>100) && (Y<200) &&  (BUTTON==2))
  { pos++; start=YES; if(pos>56) pos=56; }
  if((X>256) && (X<296) && (Y>4) && (Y<196) && (BUTTON==2))
  { num=(Y-4)/32; start=YES; }
  if((X>256) && (X<296) && (Y>4) && (Y<196) && ((BUTTON==1) && (ob!=1)))
  { num=(Y-4)/32; start=YES; }

  if((X>0) && (X<256) && (Y>4) && (Y<196) && (BUTTON==1))
  {
   a=X/32;
   b=(Y-4)/32;
   pokeb(FP_SEG(clip),FP_OFF(clip)+1024+a+b*8,pos+num);
   start=YES;
  }
  if((X>0) && (X<256) && (Y>4) && (Y<196) &&  (BUTTON==2))
  {
   a=X/32;
   b=(Y-4)/32;
   pokeb(FP_SEG(clip),FP_OFF(clip)+1024+a+b*8,64);
   start=YES;
  }


  if(start==YES)
  {
   start=NO;
   Box(256,0  ,296,199,scn,46,"",NORMAL);
   Box(256,4+num*32,296,36+num*32,scn,43,"",NORMAL);
   for(a=0;a<6;a++)
   for(b=0;b<32;b++)
   movedata(FP_SEG(data),FP_OFF(data)+b*32+a*1024+pos*1024,
            FP_SEG(scn ),FP_OFF(scn )+b*320+a*32*320+260+4*320,32);

   for(a=0;a<8;a++)
   for(b=0;b<6;b++)
   {
    d=peekb(FP_SEG(clip),FP_OFF(clip)+1024+a+b*8);
    if(d!=64)
    for(c=0;c<32;c++)
     movedata(FP_SEG(data),FP_OFF(data)+d*1024+c*32,
              FP_SEG(scn ),FP_OFF(scn )+a*32+b*32*320+c*320+4*320,32);
    else
    for(c=0;c<32;c++)
     movedata(FP_SEG(lib),FP_OFF(lib)+62*1024,
              FP_SEG(scn),FP_OFF(scn)+a*32+b*32*320+c*320+4*320,32);
   }
  }


  movedata(FP_SEG(scn  ),FP_OFF(scn  ),
           FP_SEG(scrap),FP_OFF(scrap),0xFA00);
  if((X<256) && (Y>4) && (Y<196))
  {
   a=X/32;
   b=(Y-4)/32;
   for(i=0;i<8;i++)
    movedata(FP_SEG(lib),FP_OFF(lib)+1024*42+i*32,
             FP_SEG(scn),FP_OFF(scn)+a*32+b*32*320+i*320+4*320,32);
   for(i=24;i<32;i++)
    movedata(FP_SEG(lib),FP_OFF(lib)+1024*42+i*32,
             FP_SEG(scn),FP_OFF(scn)+a*32+b*32*320+i*320+4*320,32);
   for(i=8;i<24;i++)
    movedata(FP_SEG(lib),FP_OFF(lib)+1024*42+i*32,
             FP_SEG(scn),FP_OFF(scn)+a*32+b*32*320+i*320+4*320,8);
   for(i=8;i<24;i++)
    movedata(FP_SEG(lib),FP_OFF(lib)+1024*42+i*32+24,
             FP_SEG(scn),FP_OFF(scn)+24+a*32+b*32*320+i*320+4*320,8);
  }

  if((X<20) && (Y<10))
  {
    drawmouse=NO;
    for(i=0;i<32;i++)
    movedata(FP_SEG(lib),FP_OFF(lib)+1024*47+i*32,
             FP_SEG(scn),FP_OFF(scn)+i*320,32);
  }
  else
  if((X<20) && (Y>190))
  {
    drawmouse=NO;
    for(i=0;i<32;i++)
    movedata(FP_SEG(lib),FP_OFF(lib)+1024*47+i*32,
             FP_SEG(scn),FP_OFF(scn)+(168+i)*320,32);
  }
  if((((X<20) && (Y<10 )) ||
      ((X<20) && (Y>190))) && (ob==0) && (BUTTON==1)) exit=YES;
  Draw_Mouse();
  movedata(FP_SEG(scrap),FP_OFF(scrap),
           FP_SEG(scn  ),FP_OFF(scn  ),0xFA00);
  drawmouse=YES;
  }
 drawmouse=YES; osize=9;
}