// ��ʱ��ͼ maphere.c
// Modify by zjpwxh@sjpl 2004.4.24
// Modify by zjpwxh@sjpl 2004.6.2
// �Ľ��������㷨���Թ�ȱ�������ݹ�
// ��������Ӱ���ٶȣ��ݹ���õ��£��������Խ��д������ʹ����Ӧ�ü�����Ѫ

#include <ansi.h>
#define MaxX 15
#define MaxY 20
#define MinX 7
#define MinY 10
inherit F_CLEAN_UP;

nosave int X,Y;
nosave mixed m;
nosave array rfile;
nosave mapping *data;
int draw_room(int,int,object);
void set_room(int,int,object);
void set_x_y(int,int,int);

// ת����ɫ
string clean_color(string arg)
{
       if(!arg)       return "";
       arg = replace_string(arg, BLK, "");
       arg = replace_string(arg, RED, "");
       arg = replace_string(arg, GRN, "");
       arg = replace_string(arg, YEL, "");
       arg = replace_string(arg, BLU, "");
       arg = replace_string(arg, MAG, "");
       arg = replace_string(arg, CYN, "");
       arg = replace_string(arg, WHT, "");
       arg = replace_string(arg, HIR, "");
       arg = replace_string(arg, HIG, "");
       arg = replace_string(arg, HIY, "");
       arg = replace_string(arg, HIB, "");
       arg = replace_string(arg, HIM, "");
       arg = replace_string(arg, HIC, "");
       arg = replace_string(arg, HIW, "");
       arg = replace_string(arg, NOR, "");
       arg = replace_string(arg, BLINK,"");
       return arg;
}

int main(object me, string arg)
{
       object where;
       int i,j,k,l,n,p;
       int lineu,lined,linef;
       array text;
       string tmp;

if( !wizardp(me) )
        return 0; // �ݲ�����
       if(me->query("qi") < 100)
              return notify_fail("���������̫���ˣ�����Ϣһ�°ɣ�\n");
       me->add("qi",-50);

       if(arg && arg == "-m")
       {
              X=MaxX;
              Y=MaxY;
       }
       else
       {
              X=MinX;
              Y=MinY;
       }

       tmp="�ʱ��ͼv2.0 (by zjpwxh) 2004/4/24  ���ͼ��С��"+X+"/"+Y+"\n\n";
       m=allocate(2*X+1);
       data=allocate((2*X+1)*(2*Y+1));
       rfile=({});
       for(i=0;i<2*X+1;i++)
       {
              m[i]=allocate(2*Y+1);
              for(j=0;j<2*Y+1;j++)
                     m[i][j]=" ";
       }

       where=environment(me);
       if(!objectp(where))
              return notify_fail("�Բ��𣬲�֪���㵽��������ѽ������ʦ�ɣ�\n");

       draw_room((2*X+1)/2,(2*Y+1)/2,where);

       for(l=0,linef=1;l<2*Y+1;l++)
       {
              for(n=0;n<2*X+1;n++)
              {
                     if( m[n][l]!=" ")
                            p++;
              }
              if(!p && linef)
              {
                     lineu++;
                     linef=1;
              }
              else        linef=0;
              p=0;
       }
       for(l=2*Y,linef=1;l>=0;l--)
       {
              for(n=0;n<2*X+1;n++)
              {
                     if( m[n][l]!=" ")
                            p++;
              }
              if(!p && linef)
              {
                     lined++;
                     linef=1;
              }
              else        linef=0;
              p=0;
       }

       for(i=lineu;i<2*Y+1-lined;i++)
       {
              for(j=0;j<2*X+1;j++)
              {
                     if( m[j][i]==" " && i%2 && j%2 )
                            tmp+="        ";
                     else
                     {
                            //�������Ϊ�գ����Ҵ�ʱjΪż���У�������ո�
                            if( m[j][i]==" " && !(j%2) )
                                   tmp+="  ";
                            else
                            {
                                   if( m[j][i]==" " )
                                          tmp+="        ";

                                   else
                                          tmp+=m[j][i];
                            }
                     }
              }
              tmp+="\n";
       }
       text=explode(tmp, "\n");
       for(i=k; k<sizeof(text); k++)
              write(text[k] + "\n");

       return 1;
}

object find_room(string path)
{
       object ob;
       if( objectp(ob=find_object(path)) || objectp(ob=load_object(path)) )
              return ob;
       return 0;
}

//���������I�J�K�L
int draw_path(int x,int y,string direc)
{
       string str;
       int xx=0,yy=0;
       switch(direc)
       {
              case "south":
              case "north":              str="   ��   ";break;
              case "southdown":
              case "northup":              str="   ��   ";break;
              case "southup":
              case "northdown":       str="   ��   ";break;
              case "east":
              case "west":              str="��";break;
              case "eastup":
              case "westdown":       str="��";break;
              case "westup":
              case "eastdown":       str="��";break;
              case "southeast":
              case "northwest":       str="�K";break;
              case "southwest":
              case "northeast":       str="�J";break;
              default:
                     return 0;
       }
       if(sscanf(direc,"%*ssouth%*s"))
              yy++;
       if(sscanf(direc,"%*snorth%*s"))
              yy--;
       if(sscanf(direc,"%*seast%*s"))
              xx++;
       if(sscanf(direc,"%*swest%*s"))
              xx--;
       if( x+xx<=0 || y+yy<=0 || x+xx>=2*X || y+yy>=2*Y )
              return 0;
       m[x+xx][y+yy]=HIW+str+NOR;
       return 1;
}

// ���ù�ȱ���Ѱ·�㷨,ʹ��ͼ����ʾ���Ӻ���
int draw_room(int x,int y,object room)
{
       int i,xx,yy;
       int front,rear;
       array dirs;
       object froom,nroom;
       mapping dir,x_y;
       object *queue;
       front=0;rear=0;

       queue=allocate( (2*X+1)*(2*Y+1) );
       reset_eval_cost();
       if( x<0 || y<0 || !objectp(room) || x>2*X || y>2*Y )
              return 0;

       rfile=rfile + ({ base_name(room) });
       queue[rear]=room;
       set_room(x,y,room);
       set_x_y(x,y,rear);
       rear++;

       while( front < rear )
       {
              reset_eval_cost();
              froom=queue[front];
              x_y=data[front];
              front++;
              dir=froom->query("exits");
              if( !mapp(dir) || sizeof(dir)<1 )
                     return 0;
              dirs=keys(dir);
                     for(i=0;i<sizeof(dirs);i++)
              {
                              nroom=find_room(dir[dirs[i]]);
                              if(!objectp(nroom) || member_array(base_name(nroom),rfile)!=-1)
                                     continue;
                              xx=0;yy=0;
                     if( sscanf(dirs[i],"%*ssouth%*s"))
                            yy+=2;
                     if( sscanf(dirs[i],"%*snorth%*s"))
                            yy-=2;
                     if( sscanf(dirs[i],"%*seast%*s"))
                            xx+=2;
                     if( sscanf(dirs[i],"%*swest%*s"))
                            xx-=2;
                     if( x_y["xst"]+xx<0 || x_y["yst"]+yy<0 || x_y["xst"]+xx>2*X || x_y["yst"]+yy>2*Y )
                            continue;
                     if( m[x_y["xst"]+xx][x_y["yst"]+yy]!=" ")
                            continue;
                     if( !draw_path(x_y["xst"],x_y["yst"],dirs[i]) || (xx==0&&yy==0))
                            continue;
                     rfile=rfile + ({ base_name(nroom) });
                     queue[rear]=nroom;
                     set_room(x_y["xst"]+xx,x_y["yst"]+yy,nroom);
                     set_x_y(x_y["xst"]+xx,x_y["yst"]+yy,rear);
                     rear++;
              }
       }
}

void set_room(int x,int y,object room)
{
       int i,d,xx,yy,flag;
       string name;
       mapping dir;
       array dirs;

       // ��ȡ����ɫ�ķ���short����
       name=clean_color(room->query("short"));

       // ����Ķ����������4����������
       if(strlen(name)>8)  name=name[0..7];

       if(strlen(name)<7) //�Բ���4�����ֵķ��������о��д���
       {
              d=8-strlen(name);
              if( d%2 )
              {
                     name+=" ";
                     d--;
              }
              for(i=0;i<d/2;i++)
                     name=" "+name+" ";
       }

       dir=room->query("exits");
       if( !mapp(dir) || sizeof(dir)<1 )
              flag=1;
       dirs=keys(dir);
       for(i=0;i<sizeof(dirs);i++)
       {
              xx=0;yy=0;
              if( sscanf(dirs[i],"%*ssouth%*s"))
                     yy+=2;
              if( sscanf(dirs[i],"%*snorth%*s"))
                     yy-=2;
              if( sscanf(dirs[i],"%*seast%*s"))
                     xx+=2;
              if( sscanf(dirs[i],"%*swest%*s"))
                     xx-=2;
              if( xx==0 && yy==0 )
                     flag=1;
       }

       if( flag ) name=HIY+name;
       if((x==(2*X+1)/2)&&(y==(2*Y+1)/2))
              name=BLINK+HIC+name;
       name+=NOR;
       m[x][y]=name;
}

void set_x_y(int x,int y,int rear)
{
       data[rear]=([
              "xst":x,
              "yst":y,
       ]);
}

int help(object me)
{
       write(@HELP
ָ���ʽ��maphere [-m]

�������������˽���Χ�ķ����ͼ�ķֲ�״��������־������֮������������
���ӱ�־�м�ͷ��ָ������Ƹ��ߣ��в��淶���ڵķ����Ի�ɫ��־����������
��������˸����־�����ڷ�������ص���Ե�ʣ���Щ���佫�޷���ʾ������

������Ĭ����x=7,y=10 �ĵ�ͼ��С��ʾ��ʹ��-mѡ������x=15,y=20 ��ʾ��
HELP);
       return 1;
}