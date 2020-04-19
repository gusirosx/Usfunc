#include <stdio.h>
#include <string.h>
void VTK(int,int,int,double [*],double [*],double [*],
         double [*][*][*],double [*][*][*],double [*][*][*]);
void treeTOone(int,int,int,double [*][*][*],double [*]);
char a_name[10][100];
int main()
{
    int i,j,k;
    int N=5, nx=N+1,ny=N+1,nz=N+1;
    double M3D_1[nx-1][ny-1][nz-1],
           M3D_2[nx-1][ny-1][nz-1],
           M3D_3[nx-1][ny-1][nz-1];
    double dx,dy,dz,x[nx],y[ny],z[nz];
    dx = 1.0/(N-1.0); 
    dy = dx;
    dz = dx;
    for (i=0;i<=N;i++)
    {
        x[i] = i*dx;
        y[i] = i*dy;
        z[i] = i*dz;
    }
    for (k=0;k<nz-1;k++) 
    {
        for (j=0;j<ny-1;j++) 
        {
            for (i=0;i<nx-1;i++)
            {
                M3D_1[i][j][k] = (i+1)*(j+1)*(k+1);
                M3D_2[i][j][k] = (i+1)*(j+1)*(k+1)*0.7;
                M3D_3[i][j][k] = (i+1)*(j+1)*(k+1)*0.2;
            }
        }
    }
    strcpy(a_name[0],"Array3D.vtk"); //File Name
    strcpy(a_name[1],"array_A");     //Array 1 Flag
    strcpy(a_name[2],"array_B");     //Array 2 Flag
    strcpy(a_name[3],"array_C");     //Array 3 Flag
    VTK(nx,ny,nz,x,y,z,M3D_1,M3D_2,M3D_3);
}
void treeTOone(int nx, int ny, int nz,double array3D[nx][ny][nz],double array1D[nx*ny*nz])
{
    int i,j,k,l=0;
    for (k=0;k<nz;k++) 
    {
        for (j=0;j<ny;j++) 
        {
            for (i=0;i<nx;i++)
            {
                array1D[l] = array3D[i][j][k];
                l++;
            }
        }
    }
}
void VTK(int nx, int ny, int nz,
         double x[nx],double y[ny],double z[nz],
         double array3D_1[nx-1][ny-1][nz-1],
         double array3D_2[nx-1][ny-1][nz-1],
         double array3D_3[nx-1][ny-1][nz-1])
{
    int i,l=0,Ntot=(nx-1)*(ny-1)*(nz-1);
    double array_1D[Ntot];
    FILE* f = fopen(a_name[0],"w");
    fprintf(f, "# vtk DataFile Version 3.0");
    fprintf(f, "\nNon-uniform Rectilinear - Rectilinear Grid");
    fprintf(f, "\nASCII");
    fprintf(f, "\nDATASET RECTILINEAR_GRID");
    fprintf(f, "\nDIMENSIONS   %d   %d   %d",nx,ny,nz);
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
    fprintf(f, "\nZ_COORDINATES   %d float",nz);
    for (i=0;i<nz;i++)
    {
        fprintf(f,"\n%14.6lf",z[i]);
    }
    fprintf(f, "\nCELL_DATA       %d",Ntot);
    treeTOone(nx-1,ny-1,nz-1,array3D_1,array_1D);
    fprintf(f, "\nSCALARS %s float",a_name[1]);
    fprintf(f, "\nLOOKUP_TABLE default");
    for (i=0; i<Ntot;i++)
    {
        fprintf(f,"\n%22.14lf",array_1D[i]);
    }
    treeTOone(nx-1,ny-1,nz-1,array3D_2,array_1D);
    fprintf(f, "\nSCALARS %s float",a_name[2]);
    fprintf(f, "\nLOOKUP_TABLE default");
    for (i=0; i<Ntot;i++)
    {
        fprintf(f,"\n%22.14lf",array_1D[i]);
    }
    treeTOone(nx-1,ny-1,nz-1,array3D_3,array_1D);
    fprintf(f, "\nSCALARS %s float",a_name[3]);
    fprintf(f, "\nLOOKUP_TABLE default");
    for (i=0; i<Ntot;i++)
    {
        fprintf(f,"\n%22.14lf",array_1D[i]);
    }
    fclose(f);
}
