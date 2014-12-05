program acpc10a
    implicit none
    integer :: x, y, z, ratio, delta
    do while (.true.)
        read(*,*) x, y, z
        if (x==0 .and. y==0) then
            call exit(0)
        end if
        delta = y - x
        if (z == (y+delta)) then
            write(*,'(A,I0)') 'AP ', z+delta
        else
            ratio = y / x
            write(*,'(A,I0)') 'GP ', z*ratio
        end if
    end do
end program acpc10a
