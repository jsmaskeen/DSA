#include <stdio.h>
#include <stdlib.h>

int check_all_engaged(int arr[],int n){
    for(int i =0;i<n;i++){
        if (arr[i] == 0){
            return 0;
        }
    }
    return 1;
}

int get_not_enganged_man_idx(int arr[],int n){
    for (int i=0;i<n;i++){
        if (arr[i] == 0){
            return i;
        }
    }
}

int get_top_pref_idx(int arr[],int n){
    for (int i=0;i<n;i++){
        if (arr[i] != 0){
            return i;
        }
    }
}

int is_x_prefered_over_y(int arr[],int x,int y,int n){
    int idx_x;
    int idx_y;
    for (int i=0;i<n;i++){
        if (arr[i] == x){
            idx_x = i;
        }
        if (arr[i] == y){
            idx_y = i;
        }
    }
    if (idx_x < idx_y){
        return 1;
    }
    else {
        return 0;
    }
}

int main() {
    int n;
    scanf("%d",&n);
    // printf("%d\n",n);
    int men[n][n];
    int women[n][n];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d",&men[i][j]);
            // scanf("%d",men[i][j]);
        }    
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d",&women[i][j]);
        }   
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d",men[i][j]);
        }
        printf("\n");
        
    }
    // return 0;
    int engaged_men[n];
    int engaged_women[n];
    for(int i=0;i<n;i++){
        engaged_men[i] = 0;
        engaged_women[i] = 0;
    }

    while (check_all_engaged(engaged_men,n) == 0)
    {
        int uneng_man_idx = get_not_enganged_man_idx(engaged_men,n);
        int pref_women_idx = get_top_pref_idx(men[uneng_man_idx],n);
        int w = men[uneng_man_idx][pref_women_idx];
        if (engaged_women[w-1] == 0){
            engaged_women[w-1] = uneng_man_idx+1;
            engaged_men[uneng_man_idx] = w;
            // ask out ko 0 karo
            men[uneng_man_idx][pref_women_idx] = 0;

        } else {
            int curr_fiance = engaged_women[w-1];
            if (is_x_prefered_over_y(women[w-1],uneng_man_idx+1,curr_fiance,n) == 1){
                engaged_women[w-1] = uneng_man_idx+1;
                engaged_men[uneng_man_idx] = w;
                men[uneng_man_idx][pref_women_idx] = 0;
                engaged_men[curr_fiance-1] = 0;
            }
            else{
                men[uneng_man_idx][pref_women_idx] = 0;
            }

        }

    }
    for(int i=0;i<n;i++){
        printf("%d %d \n",i+1,engaged_women[i]);
    }

}