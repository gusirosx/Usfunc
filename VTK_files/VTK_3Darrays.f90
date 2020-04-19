program VTK
    implicit none
    double precision, allocatable, dimension(:):: x,y,z
    double precision,allocatable,dimension(:,:,:)::M3D_1,M3D_2,M3D_3
    double precision :: dx,dy,dz
    integer :: i,j,k,N
    integer :: nx,ny,nz
    N = 5
    nx = N+1; ny = N+1; nz = N+1;
    allocate(M3D_1(N,N,N),M3D_2(N,N,N),M3D_3(N,N,N),x(nx),y(ny),z(nz))
    dx = 1.0d0/(N-1.0d0) 
    dy = dx
    dz = dx
    do i = 1, N+1
        x(i) = (i-1.0d0)*dx
        y(i) = (i-1.0d0)*dy
        z(i) = (i-1.0d0)*dz
    end do
    do k = 1, N
        do j = 1, N
            do i = 1, N
                M3D_1(i,j,k) = i*j*k
                M3D_2(i,j,k) = i*j*k*0.7d0;
                M3D_3(i,j,k) = i*j*k*0.2d0;
            end do
        end do
    end do
    open(unit=1, file ='contour3D.vtk')
    write ( 1,'(a)' )'# vtk DataFile Version 3.0'
    write ( 1,'(a)' ) 'Non-uniform Rectilinear - Rectilinear Grid'
    write ( 1,'(a)' ) 'ASCII'
    write ( 1,'(a)' ) 'DATASET RECTILINEAR_GRID'
    write ( 1,'(a,3i4)' )'DIMENSIONS', nx,ny,nz
    write ( 1,'(a13,1i4,a6)' ) 'X_COORDINATES',nx,' float'
    write ( 1,'(f14.6)' ) (x(i),i=1,nx)
    write ( 1,'(a13,1i4,a6)' ) 'Y_COORDINATES',ny,' float'
    write ( 1,'(f14.6)' ) (y(j),j=1,ny)
    write ( 1,'(a13,1i4,a6)' ) 'Z_COORDINATES',nz,' float'
    write ( 1,'(f14.6)' ) (z(k),k=1,nz)
    write ( 1, '(a, I16)' ) 'CELL_DATA ', (nx-1)*(ny-1)*(nz-1)
    write ( 1, '(a)' ) 'SCALARS array_A float'
    write ( 1, '(a)' ) 'LOOKUP_TABLE default'
    write ( 1, '(f22.14)' ) (((M3D_1(i,j,k),i=1,(nx-1)),j=1,(ny-1)),k=1,(nz-1))
    write ( 1, '(a)' ) 'SCALARS array_B float'
    write ( 1, '(a)' ) 'LOOKUP_TABLE default'
    write ( 1, '(f22.14)' ) (((M3D_2(i,j,k),i=1,(nx-1)),j=1,(ny-1)),k=1,(nz-1))
    write ( 1, '(a)' ) 'SCALARS array_C float'
    write ( 1, '(a)' ) 'LOOKUP_TABLE default'
    write ( 1, '(f22.14)' ) (((M3D_3(i,j,k),i=1,(nx-1)),j=1,(ny-1)),k=1,(nz-1))    
    deallocate(M3D_1,M3D_2,M3D_3)
end program VTK
