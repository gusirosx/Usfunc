program VTK2D
    implicit none
    double precision, allocatable, dimension(:):: x,y
    double precision,allocatable,dimension(:,:)::M2D_1,M2D_2,M2D_3
    double precision :: dx,dy
    integer :: i,j,N
    integer :: nx,ny,nz
    N = 5
    nx = N+1; ny = N+1;
    allocate(M2D_1(N,N),M2D_2(N,N),M2D_3(N,N),x(nx),y(ny))
    dx = 1.0d0/(N-1.0d0) 
    dy = dx
    do i = 1, N+1
        x(i) = (i-1.0d0)*dx
        y(i) = (i-1.0d0)*dy
    end do
    do j = 1, N
        do i = 1, N
            M2D_1(i,j) = i*j
            M2D_2(i,j) = i*j*0.7d0;
            M2D_3(i,j) = i*j*0.2d0;
        end do
    end do
    open(unit=1, file ='Array2D.vtk')
    write ( 1,'(a)' )'# vtk DataFile Version 3.0'
    write ( 1,'(a)' ) 'Non-uniform Rectilinear - Rectilinear Grid'
    write ( 1,'(a)' ) 'ASCII'
    write ( 1,'(a)' ) 'DATASET RECTILINEAR_GRID'
    write ( 1,'(a,3i4)' )'DIMENSIONS', nx,ny,1
    write ( 1,'(a13,1i4,a6)' ) 'X_COORDINATES',nx,' float'
    write ( 1,'(f14.6)' ) (x(i),i=1,nx)
    write ( 1,'(a13,1i4,a6)' ) 'Y_COORDINATES',ny,' float'
    write ( 1,'(f14.6)' ) (y(j),j=1,ny)
    write ( 1,'(a13,1i4,a6)' ) 'Z_COORDINATES',1,' float'
    write ( 1,'(f14.6)' ) 1.0
    write ( 1, '(a, I16)' ) 'CELL_DATA ', (nx-1)*(ny-1)*1
    write ( 1, '(a)' ) 'SCALARS array_A float'
    write ( 1, '(a)' ) 'LOOKUP_TABLE default'
    write ( 1, '(f22.14)' ) ((M2D_1(i,j),i=1,(nx-1)),j=1,(ny-1))
    write ( 1, '(a)' ) 'SCALARS array_B float'
    write ( 1, '(a)' ) 'LOOKUP_TABLE default'
    write ( 1, '(f22.14)' ) ((M2D_2(i,j),i=1,(nx-1)),j=1,(ny-1))
    write ( 1, '(a)' ) 'SCALARS array_C float'
    write ( 1, '(a)' ) 'LOOKUP_TABLE default'
    write ( 1, '(f22.14)' ) ((M2D_3(i,j),i=1,(nx-1)),j=1,(ny-1))
    close(1)
    deallocate(M2D_1,M2D_2,M2D_3)
end program VTK2D
