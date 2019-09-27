#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define EMP_DB_FILE "emp.db"

typedef struct emp
{
	int empno;
	int sal;
	char ename[24];
}emp_t;

void accept_emp(emp_t *e)
{
	printf("enter empno, ename & sal : ");
	scanf("%d%s%d", &e->empno, e->ename, &e->sal);
}

void print_emp(emp_t *e)
{
	printf("%d, %s, %d\n", e->empno, e->ename, e->sal);
}

void add_emp()
{
	int fd;
	emp_t e;
	accept_emp(&e);
	fd = open(EMP_DB_FILE, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if(fd < 0)
	{
		perror("open() failed");
		_exit(1);
	}

	write(fd, &e, sizeof(e));

	close(fd);
}

void display_all_emp()
{
	emp_t e;
	int fd;

	fd = open(EMP_DB_FILE, O_RDONLY);
	if(fd < 0)
	{
		perror("open() failed");
		_exit(1);
	}

	while(read(fd, &e, sizeof(e)) > 0)
	{
		print_emp(&e);
	}

	close(fd);
}

void edit_emp()
{
	int fd;
	emp_t e, ne;
	int empno;
	long size = sizeof(emp_t); // 32

	printf("enter empno to be edited : ");
	scanf("%d", &empno);

	fd = open(EMP_DB_FILE, O_RDWR);
	if(fd < 0)
	{
		perror("open() failed");
		_exit(1);
	}

	while(read(fd, &e, sizeof(e)) > 0)
	{
		if(e.empno == empno)
		{
			printf("Record Found : ");
			print_emp(&e);

			printf("Enter New Details : \n");
			accept_emp(&ne);

			lseek(fd, -size, SEEK_CUR);
			write(fd, &ne, sizeof(ne));
			break;
		}
	}
	close(fd);
}
int main()
{
	//add_emp();
	edit_emp();
	display_all_emp();
	return 0;
}

