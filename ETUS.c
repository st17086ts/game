/* simulator */
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
/*#include <sys/un.h>
#include <unistd.h>*/
#include <string.h>

#define N 400 
#define OID (id^1)
#define CLIENT_0 "client_0"
#define CLIENT_1 "client_1"


const int SCT[2][2]={{7256,9},{5,3211}};

int play_0(int ID, int n,int SC[2] , int *H);
int play_1(int ID, int n,int SC[2] , int *H);

int Compare(int i, int j);
int Compute(int p, int q, int n);
void Evaluate(int p,int q,int *sum1, int *sum2, int n, int SC, int *t);

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

//play_0‘¤‚Å‚â‚éê‡‚Í‚±‚¿‚ç‚ÌŠÖ”
int play_0(int ID,int n,int SC[2] , int *H)
{
    if(SCT[0][1] > SCT[1][0]) return 0;
    else{
        return 1;
    }
}

//play_1‘¤‚Å‚â‚éê‡‚Í‚±‚¿‚ç‚ÌŠÖ”
int play_1(int ID,int n,int SC[2] , int *H)
{
 if(SCT[0][1] > SCT[1][0]) return 0;
 else return 1;
}

