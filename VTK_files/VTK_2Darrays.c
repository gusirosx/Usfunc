#include <stdio.h>
#include <string.h>
void VTK(int,int,double [*],double [*],
         double [*][*],double [*][*],double [*][*]);
void twoTOone(int,int,double [*][*],double [*]);
char a_name[10][100];
int main()
{
    int i,j;
    int N=5, nx=N+1,ny=N+1;
    double M2D_1[nx-1][ny-1],
           M2D_2[nx-1][ny-1],
           M2D_3[nx-1][ny-1];
    double dx,dy,x[nx],y[ny];
    dx = 1.0/(N-1.0); 
    dy = dx;
    for (i=0;i<=N;i++)
    {
        x[i] = i*dx;
        y[i] = i*dy;
    }
    for (j=0;j<ny-1;j++) 
    {
        for (i=0;i<nx-1;i++)
        {
            M2D_1[i][j] = (i+1)*(j+1);
            M2D_2[i][j] = (i+1)*(j+1)*0.7;
            M2D_3[i][j] = (i+1)*(j+1)*0.2;
        }
    }
    strcpy(a_name[0],"Array2D.vtk"); //File Name
    strcpy(a_name[1],"array_A");     //Array 1 Flag
    strcpy(a_name[2],"array_B");     //Array 2 Flag
    strcpy(a_name[3],"array_C");     //Array 3 Flag
    VTK(nx,ny,x,y,M2D_1,M2D_2,M2D_3);
}
void twoTOone(int nx, int ny,double array2D[nx][ny],double array1D[nx*ny])
{
    int i,j,l=0;
    for (j=0;j<ny;j++) 
    {
        for (i=0;i<nx;i++)
        {
            array1D[l] = array2D[i][j];
            l++;
        }
    }
}
void VTK(int nx, int ny,
         double x[nx],double y[ny],
         double array2D_1[nx-1][ny-1],
         double array2D_2[nx-1][ny-1],
         double array2D_3[nx-1][ny-1])
{
    int i,l=0,Ntot=(nx-1)*(ny-1);
    double array_1D[Ntot];
    FILE* f = fopen(a_name[0],"w");
    fprintf(f, "# vtk DataFile Version 3.0");
    fprintf(f, "\nNon-uniform Rectilinear - Rectilinear Grid");
    fprintf(f, "\nASCII");
    fprintf(f, "\nDATASET RECTILINEAR_GRID");
    fprintf(f, "\nDIMENSIONS   %d   %d   1",nx,ny);
    fprintf(f, "\nX_COORDINATES   %d float",nx);
    for (i=0;i<nx;i++)
    {
        fprintf(f,"\n%14.6lf",x[i]);
    } 
    fprintf(f, "\nY_COORDINATES   %d float",ny);
    for (i=0;i<ny;i++)
    {
        fprintf(f,"\n%14.6lf",y[i]);
    }  
    fprintf(f, "\nZ_COORDINATES   1 float");
    fprintf(f,"\n      1.000000");
    fprintf(f, "\nCELL_DATA       %d",Ntot);
    twoTOone(nx-1,ny-1,array2D_1,array_1D);
    fprintf(f, "\nSCALARS %s float",a_name[1]);
    fprintf(f, "\nLOOKUP_TABLE default");
    for (i=0; i<Ntot;i++)
    {
        fprintf(f,"\n%22.14lf",array_1D[i]);
    }
    twoTOone(nx-1,ny-1,array2D_2,array_1D);
    fprintf(f, "\nSCALARS %s float",a_name[2]);
    fprintf(f, "\nLOOKUP_TABLE default");
    for (i=0; i<Ntot;i++)
    {
        fprintf(f,"\n%22.14lf",array_1D[i]);
    }
    twoTOone(nx-1,ny-1,array2D_3,array_1D);
    fprintf(f, "\nSCALARS %s float",a_name[3]);
    fprintf(f, "\nLOOKUP_TABLE default");
    for (i=0; i<Ntot;i++)
    {
        fprintf(f,"\n%22.14lf",array_1D[i]);
    }
    fclose(f);
}
