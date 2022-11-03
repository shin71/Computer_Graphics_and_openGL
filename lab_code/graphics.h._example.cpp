#include <graphics.h>
int main()
{
  int gd = DETECT, gm;
  initgraph(&gd, &gm, NULL);
  outtextxy(10, 10 + 10, "using different inbuilt functions of  graphics.h");
    setlinestyle(0, 0, 3);
    rectangle(50, 100, 100, 50);
    bar(200, 50, 150, 100);
    circle(400, 50, 50);
    ellipse(550,50,0,360,50,40);
    line(50,200,200,100);
    putpixel(350, 100, YELLOW);
    arc(200, 300, 0, 100, 50);
    //points of ploygon 1
    int p1[]={320,150,420,300,500,300,320,150};
    //drawing polygon 1
    drawpoly(4, p1);
    sector(500, 150, 0, 300, 50, 50);
    getch();
  closegraph();
}
