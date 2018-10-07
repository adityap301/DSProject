// C code to find hospitals nearby 
#include <stdio.h> 
#include <stdlib.h>
#include <string.h> 
#include <math.h>
// Latitude of user. 
#define lat1d 19.1374845 
// Longitude of user. 
#define lon1d 72.917362214 
#define pi 3.14159265358979323846 
#define earth_radius 6371.0 

// Function to convert degree to radian. 
double degToRad(double deg) 
{ 
    return (deg * pi / 180); 
} 

/* Function to calculate distance between 2 given locations 
    using Great Circle Distance Formula. */
double distanceEarth(double lat2d, double lon2d) 
{                  
    double lat1, lon1, lat2, lon2, delta_lon, central_ang; 
    lat1 = degToRad(lat1d); // Converting latitude from degrees to radians
    lon1 = degToRad(lon1d); 
    lat2 = degToRad(lat2d); 
    lon2 = degToRad(lon2d); 
    delta_lon = lon2 - lon1; 
    /*great circle distance formula: 
        central_ang = arccos(sin(lat1) * sin(lat2) + cos(lat1) * cos(lat2) * cos(delta_lon))
        distance = radius * central_ang) */
    central_ang = acos(sin(lat1) * sin(lat2) + cos(lat1) * cos(lat2) * cos(delta_lon));                     
    return (earth_radius * central_ang); 
} 

struct node 
{ 
    char hosp_name[100], hosp_add[1000], hosp_num[50];  
    double lat2d, lon2d; 
    struct node *link;
}*head=NULL, *tail=NULL, *newnode=NULL, *temp=NULL;

void insert()
{
    char name[100], add[1000], num[50];  
    double lat, lon;
    newnode = (struct node*) malloc(sizeof(struct node));
    printf("\nEnter the name of the hospital: ");
    //gets(name);
    fgets(name, 100, stdin);
    strcpy(newnode->hosp_name, name);
    printf("\nEnter the latitude: ");
    scanf("%lf", &lat);
    newnode->lat2d = lat;
    printf("Enter the longitude: ");
    scanf("%lf", &lon);
    newnode->lon2d = lon;
    printf("\nEnter contact numbers (seperated by commas): ");
    //gets(num);
    fgets(num, 50, stdin);
    strcpy(newnode->hosp_num, num);
    printf("\nEnter the address: ");
    //gets(add);
    fgets(add, 1000, stdin);
    strcpy(newnode->hosp_add, add);    
    newnode->link = NULL;
    if(head == NULL)
    {
        head = newnode;
        tail = newnode;
    }
    else
    {
        tail->link = newnode;
        tail = newnode;
    }
}

// Function to check whether distance between 2 points is less than 5km or not. 
void distance_calculator() 
{   
    temp = head;
    int cnt = 0;
    if(temp!=NULL)
    {
        while(temp != NULL)
        {
            if (distanceEarth(temp->lat2d, temp->lon2d) <= 5.000000) 
            {
                printf("%s \n %s \n %s \n", temp->hosp_name, temp->hosp_num, temp->hosp_add);
                cnt++;  
            }
            temp = temp->link;
        }
        if(cnt == 0)
            printf("\nNo records found.");
    }
    else 
        printf("\nNo records found.");
}  
int main() 
{
    int opt, opt1;
    do
     {
        printf("Hospital menu:\n1.Insert record.\n2.Find nearby hospitals.");
        printf("\nEnter your choice:");
        scanf("%d", &opt);
        switch(opt)
        {
            case 1:
                insert();
                break;
            case 2:
                distance_calculator();
                break;
            default:
                printf("\nEnter valid option.");
        }
        printf("\nPress 1 to continue, 0 to exit: ");
        scanf("%d", &opt1);
     } while (opt1 == 1);
    return 0; 
} 

