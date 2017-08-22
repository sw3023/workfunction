#include <stdio.h>
#define NGXM 256
#define NOUTM 1024
char HEADER[80];
float VAV[NOUTM+1];
float VLOCAL[NGXM*NGXM*NGXM+1];
int IDIR;
int I, II, III, IIII;
int NIONS;
int NGX, NGY, NGZ;
int NPLWV;
int NOUT;
double SCALE;
int IX, IY, IZ;
int IPL;
FILE* FP;
int i;
int main(){
    printf("========================\n");
    printf("Workfunction V2 (2009)\n");
    printf("========================\n");
    printf("\n");
    printf("Which direction to average along? (1=x;2=y;3=z)\n");
    scanf("%d",&IDIR);
    IDIR=(IDIR+20)%3+1;
    FP=fopen("LOCPOT","r");
    if(FP==NULL){
        printf("Error opening or reading file LOCPOT!\n");
        return 1;
    }
    fgets(HEADER,80,FP);
    fgets(HEADER,80,FP);
    fgets(HEADER,80,FP);
    fgets(HEADER,80,FP);
    fgets(HEADER,80,FP);
    fgets(HEADER,80,FP);
    fgets(HEADER,80,FP);
    I=0;II=0;III=0;IIII=0;
    sscanf(HEADER,"%d %d %d %d",&I, &II, &III, &IIII);
    NIONS=I+II+III+IIII;
    printf("Number of ions:%12d\n",NIONS);
    for(i=0;i<=NIONS;i++) fgets(HEADER,80,FP);
    printf("(i) Positions read...\n");
    fgets(HEADER,80,FP);
    fgets(HEADER,80,FP);
    sscanf(HEADER,"%d %d %d",&NGX, &NGY, &NGZ);
    NPLWV=NGX*NGY*NGZ;
    if(IDIR==1) NOUT=NGX;
    if(IDIR==2) NOUT=NGY;
    if(IDIR==3) NOUT=NGZ;
    if(NPLWV>(NGXM*NGXM*NGXM)){
         printf("NPLWV .GT. NGXM**3 (%12d ).\n",NPLWV);
         return 1;
    }
    if(NOUT>NOUTM){
         printf("NOUT .GT. NOUTM (%12d ).\n",NOUT);
         return 1;
    }
    for(i=1;i<=NPLWV;i++) fscanf(FP, " %f", &(VLOCAL[i]));
    fclose(FP);
    printf("(ii) 3D potential read...\n");
    for(i=1;i<=NOUTM;i++)VAV[i]=0;
    SCALE=1.0/(NPLWV*1.0/NOUT);
    if(IDIR==1){
        for(IX=1;IX<=NGX;IX++){
            for(IZ=1;IZ<=NGZ;IZ++){
                for(IY=1;IY<=NGY;IY++){
                    IPL=IX+((IY-1)+(IZ-1)*NGY)*NGX;
                    VAV[IX]=VAV[IX]+VLOCAL[IPL]*SCALE;
                }
            }
        }
    }else if(IDIR==2){
        for(IY=1;IY<=NGY;IY++){
            for(IZ=1;IZ<=NGZ;IZ++){
                for(IX=1;IX<=NGX;IX++){
                    IPL=IX+((IY-1)+(IZ-1)*NGY)*NGX;
                    VAV[IY]=VAV[IY]+VLOCAL[IPL]*SCALE;
                }
            }
        }
    }else if(IDIR==3){
        for(IZ=1;IZ<=NGZ;IZ++){
            for(IY=1;IY<=NGY;IY++){
                for(IX=1;IX<=NGX;IX++){
                    IPL=IX+((IY-1)+(IZ-1)*NGY)*NGX;
                    VAV[IZ]=VAV[IZ]+VLOCAL[IPL]*SCALE;
                }
            }
        }
    }else{
         printf("Wrong value of IDIR',%12d\n", IDIR);
         return 1;
    }
    FP=fopen("vplanar.txt","w+");
    fprintf(FP, "%12d%12d\n",NOUT,IDIR);
    for(i=1;i<=NOUT;i++) fprintf(FP, "%6d  %18.10E\n",i,VAV[i]);
    fclose(FP);
    printf("\nDone. Always check for convergence!\n");
    return 0;
}
