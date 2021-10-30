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

const int SCT[2][2]={{3,41},{5,3211}};

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


int play_0(int ID,int n,int SC[2] , int *H)
{
    static int sumcheck1, sumcheck2;
    int t;
    //nの回数を見ることで１００，２００，３００回までを見て更新する。
    if(n <= 100){
      t = Compute(5, 10, n);
      Evaluate(5, 10,&sumcheck1, &sumcheck2, n, SC[0],&t);}
    else if(n <= 200 && n > 100){
      t = Compute(105, 110, n);
      Evaluate(105,110,&sumcheck1, &sumcheck2, n, SC[0],&t);
    }
    else{
      t = Compute(205, 210, n);
      Evaluate(205,210,&sumcheck1, &sumcheck2, n, SC[0],&t);      
    }
    
    return t;
}

int play_1(int ID,int n,int SC[2] , int *H)
{
 return 0;
}

//０と１を同じ回数出した結果のスコアを引数で渡して比較し、大きい方を返す関数
int Compare(int i, int j){
    if(i > j)
        return 1;
    else
        return 0;
}

//0と１を同じ回数出す関数
int Compute(int p, int q, int n){
  int t;
  if(n < p){
    t =  1;}
  else if(n < q && n >= p){
    t = 0;
  }
  return t;
}

//０と１を同じ回数出した結果、それぞれのスコアを計算する関数、その後Compareにスコアの結果を渡すことで行動を選択。
void Evaluate(int p, int q,int *sum1, int *sum2, int n, int SC, int *t){
  static int re=0;
  if(n == (p-4)) {
    re = SC;
    }

  //printf("%d times\n",n);
    if(n == p){
        *sum1 = SC - re;
        //printf("sumcheck1:%d\n",*sum1);
    }
    else if(n == q){
        *sum2 = SC - *sum1-re;
        //printf("%d times,sumchek2:%d\n",n,*sum2);
    }
    else{
    }

  if(n >= q)
    *t = Compare(*sum1, *sum2); 
}
