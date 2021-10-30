/* simulator */
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
/*#include <sys/un.h>
#include <unistd.h>*/
#include <string.h>

#define N 50 
#define OID (id^1) 
#define CLIENT_0 "client_0"
#define CLIENT_1 "client_1"


const int SCT[2][2]={{5,0},{10,2}};

int play_0(int ID, int n,int SC[2] , int *H);
int play_1(int ID, int n,int SC[2] , int *H);

int main(void){
  int i,j,k,t,n = N,rh[2],er ;
  char c_name[2][255];
  int server_len , client_len[2] ;

  int *h; //int h[2][N];
  int sc[2]={0,0};
  FILE *LOG;

  LOG=fopen("log_tai","w");

  setbuf(stderr,NULL);

  // Initialize
  srand((unsigned int)time(NULL));

  //calloc
  h=(int *)calloc(2*n,sizeof(int));

/////////////////////////////////////////
    for(j=0;j<n;j++){
		rh[0]=play_0(0, j, sc, h);
		rh[1]=play_1(1, j, sc, h);

		for(k=0;k<2;k++){
			*(h+(2*j)+k)=rh[k];
			sc[k] += SCT[rh[k]][rh[k^1]];
		}
		fprintf(LOG,"Turn %3d,h: %d %d, sc:%3d %3d,total: %3d %3d\n",
			j+1,
			*(h+(2*j)),*(h+(2*j)+1),
			SCT[*(h+(2*j))][*(h+(2*j)+1)],SCT[*(h+(2*j)+1)][*(h+(2*j))],
			sc[0],sc[1]);
    }

    fprintf(LOG,"      %s : %s .\n",CLIENT_0,CLIENT_1);
    fprintf(LOG,"score  %d : %d . %d\n",sc[0],sc[1],sc[0]+sc[1]);
    printf("      %s : %s .\n",CLIENT_0,CLIENT_1);
    printf("score  %d : %d . %d\n",sc[0],sc[1],sc[0]+sc[1]);
    fprintf(stderr,"\n THE END\n");

    fclose(LOG);
    return 0;
}

//play_0‚ÌŠÖ”‚ªŸ•‰‚·‚éÛAˆµ‚¤ŠÖ”
//play_1‘¤‚Ås‚¤ê‡‚Í‰º‚ÉƒRƒƒ“ƒgƒAƒEƒg‚³‚ê‚Ä‚¢‚éŠÖ”‚ðˆµ‚Á‚Ä‚­‚¾‚³‚¢B
int play_0(int ID,int n,int SC[2] , int *H)
{
  //•’Ê‚ÌéŒ¾‚¾‚ÆŠÖ”‚ªŒÄ‚Î‚ê‚é‚½‚Ñ‚Écount‚ª‚O‚É‰Šú‰»‚³‚ê‚Ä‚µ‚Ü‚¤‚½‚ßAstatic(Ã“I)‚ÅéŒ¾‚·‚é‚±‚Æ‚ÅA
  //‘O‰ñŒÄ‚Ño‚µ‚½ŠÖ”‚Å‰ÁŽZ‚³‚ê‚½count‚Ìî•ñ‚ðˆÛŽ‚³‚¹‚éB
  static int count = 0;

  //•Ï”I‚É‚Í‘O‰ñ‚Ì‘ŠŽè‚ªo‚µ‚½Žè‚ðŠi”[‚µ‚Ä‚¢‚éBiˆê‰ñ•ªj
  int I = *(H + 2* n - 1);
  int J = *(H + 2*n - 2);

  //ˆê‰ñ–Ú‚Æ“ñ‰ñ–Ú‚Í— Ø‚éB
  if(n == 0 || n == 1){
    return 1;
  }
  else//“ñ‰ñ–ÚˆÈ~
  {
    //‘ŠŽè‚ª‹­’²‚µ‚½‚çcount‚É‚P‚½‚·B
    if(I == 0){
      count++;
    }
    else{
      count = 0;
    }
  }

  //count‚ª“ñ‰ñˆÈã‚Ìê‡‚Í‚±‚¿‚ç‚à‹­’²‚µA— Ø‚Á‚½ê‡‚Ícount‚É‚O‚ªŠi”[‚³‚ê‚ÄÄ‚Ñ— Ø‚éB
  if(count >= 2){
    return 0;
  }
  else{
    return 1;
  }
    
}

int play_1(int ID,int n,int SC[2] , int *H)
{
  int  t,i,j;

  if(ID == 0){
    t = rand() & 1;
  }

  if(ID == 1){
    t = (rand()>>1) & 1;
  }

  return t;
}

/*
//play_1‚ÌŠÖ”‚ªŸ•‰‚·‚éÛAˆµ‚¤ŠÖ”
int play_1(int ID,int n,int SC[2] , int *H)
{
  //•’Ê‚ÌéŒ¾‚¾‚ÆŠÖ”‚ªŒÄ‚Î‚ê‚é‚½‚Ñ‚Écount‚ª‚O‚É‰Šú‰»‚³‚ê‚Ä‚µ‚Ü‚¤‚½‚ßAstatic(Ã“I)‚ÅéŒ¾‚·‚é‚±‚Æ‚ÅA
  //‘O‰ñŒÄ‚Ño‚µ‚½ŠÖ”‚Å‰ÁŽZ‚³‚ê‚½count‚Ìî•ñ‚ðˆÛŽ‚³‚¹‚éB
  static int count = 0;

  //•Ï”I‚É‚Í‘O‰ñ‚Ì‘ŠŽè‚ªo‚µ‚½Žè‚ðŠi”[‚µ‚Ä‚¢‚éBiˆê‰ñ•ªj
  int I = *(H + 2*n - 2);

  //ˆê‰ñ–Ú‚Æ“ñ‰ñ–Ú‚Í— Ø‚éB
  if(n == 0 || n == 1){
    return 1;
  }
  else//“ñ‰ñ–ÚˆÈ~
  {
    //‘ŠŽè‚ª‹­’²‚µ‚½‚çcount‚É‚P‚½‚·B
    if(I == 0){
      count++;
    }
    else{
      count = 0;
    }
  }

  //count‚ª“ñ‰ñˆÈã‚Ìê‡‚Í‚±‚¿‚ç‚à‹­’²‚µA— Ø‚Á‚½ê‡‚Ícount‚É‚O‚ªŠi”[‚³‚ê‚ÄÄ‚Ñ— Ø‚éB
  if(count >= 2){
    return 0;
  }
  else{
    return 1;
  }
    
}
*/