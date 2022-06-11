#include <stdio.h>	
#include <Windows.h>
#include <conio.h>

int a[302][302], b[302][302];
int n, m, sgen, interval, gen = 1;
int birth = 3, survive = 2, death = 4;
char command[500];

void gotoxy(int x, int y)
{
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void start()
{
	system("mode con cols=75 lines=19");
	printf("***************************************************************************\n");
	printf("*                           콘웨이의 생명 게임                            *\n");
	printf("***************************************************************************\n");
	printf("*Conway's Game of Life, 줄여서 Life Game 은 영국의 수학자 존 호튼 콘웨이가*\n");
	printf("*구현한 세포 자동자 게임입니다.                                           *\n");
	printf("*이는 바둑판처럼 정사각형의 여러 칸으로 나뉘어진 공간에서 한 칸에         *\n");
	printf("*한 마리씩 있는 세포들의 삶과 죽음이 펼쳐지는 게임입니다.                 *\n");
	printf("*생명 게임의 규칙은 빈 칸 주위 8칸에 다른 세포가 정확히 3개 있으면        *\n");
	printf("*그 다음 세대에 그 칸에 세포가 생성되고,                                  *\n");
	printf("*이미 세포가 있는 칸 주위 8칸에 2개 또는 3개의 세포가 있으면              *\n");
	printf("*그 칸의 세포는 다음 세대에 살아남은 상태를 유지합니다.                   *\n");
	printf("*그 이외의 경우, 해당 칸의 세포는 고립되거나 과밀해져                     *\n");
	printf("*죽게 됩니다.                                                             *\n");
	printf("*처음 세포들의 위치를 입력하면 그 규칙에 따라 삶과 죽음이 일어나는 것을   *\n");
	printf("*재미있게 구경하면 됩니다!                                                *\n");
	printf("***************************************************************************\n");
	char keypress;
	while (1)
	{
		gotoxy(30, 17);
		printf("*Press Enter*");
		Sleep(500);
		if (_kbhit())
		{
			keypress = _getch();
			if (keypress == 13)
				break;
		}
		gotoxy(30, 17);
		printf("              ");
		Sleep(500);
		if (_kbhit())
		{
			keypress = _getch();
			if (keypress == 13)
				break;
		}
	}
	system("cls");
	system("mode con cols=55 lines=6");
	printf("*******************************************************\n");
	printf("*생명 게임을 진행할 공간을 행, 열 순으로 입력해주세요.*\n");
	printf("*******************************************************\n");
	gotoxy(0, 5);
	printf("*******************************************************");
	gotoxy(0, 3);
	printf("*                                                     *");
	gotoxy(0, 4);
	printf("*                                                     *");
	gotoxy(3, 3);
	printf("행 :");
	gotoxy(8, 3);
	scanf("%d", &n);
	gotoxy(3, 4);
	printf("열 :");
	gotoxy(8, 4);
	scanf("%d", &m);
	system("cls");
	int l, c;
	if (n < 10)
		l = 10;
	else
		l = n;
	if (m < 10)
		c = 10;
	else
		c = m;
	sprintf(command, "mode con lines=%d cols=%d", l+5, c*2);
	system(command);
}

void setCell()
{
	gotoxy(0, 0);
	int x = (m/2)*2;
	int y = n / 2;
	int key;
	int go = 0;
	while(1)
	{
		gotoxy(0, 0);
		for (int i = 1; i <= n; i++, puts(""))
		{
			for (int j = 1; j <= m; j++)
			{
				if (a[i][j])
					printf("■");
				else
					printf("□");
			}
		}
		gotoxy(0, n + 1);
		printf("x:%d y:%d", x / 2 + 1, y + 1);
		gotoxy(0, n + 2);
		printf("방향키와 스페이스를 사용해 세포를 배치합니다.\n배치가 끝나면 엔터를 눌러주세요.");
		gotoxy(x, y);
		key = _getch();
		switch (key)
		{
		case 224:
			key = _getch();
			switch (key)
			{
			case 72://상
				if (y != 0)
					y--;
				break;
			case 75://좌
				if (x != 0)
					x-=2;
				break;
			case 77://우
				if (x != m*2)
					x+=2;
				break;
			case 80://하
				if (y != n)
					y++;
				break;
			default:
				break;
			}
			break;
		case 32:
			if (a[y + 1][x / 2 + 1] == 0)
			{
				a[y + 1][x / 2 + 1] = 1;
				printf("■");
			}
			else
			{
				a[y + 1][x / 2 + 1] = 0;
				printf("□");
			}
			break;
		case 13:
			go = 1;
		default:
			break;
		}
		system("cls");
		if (go)
			break;
	}
	
}

void setGI()
{
	system("mode con cols=58 lines=6");
	printf("*********************************************************\n");
	printf("*생명 게임을 진행할 세대 수와 세대 간 간격을 정해주세요.*\n");
	printf("*********************************************************\n");
	gotoxy(0, 5);
	printf("*********************************************************");
	gotoxy(0, 3);
	printf("*                                                       *");
	gotoxy(0, 4);
	printf("*                                                       *");
	gotoxy(3, 3);
	printf("세대 :");
	gotoxy(10, 3);
	scanf("%d", &sgen);
	gotoxy(3, 4);
	printf("간격(ms) :");
	gotoxy(14, 4);
	scanf("%d", &interval);
	int l, c;
	if (n < 10)
		l = 10;
	else
		l = n;
	if (m < 10)
		c = 10;
	else
		c = m;
	sprintf(command, "mode con lines=%d cols=%d", l + 5, c * 2);
	system(command);
}

int main()
{
	start();
	setCell();
	setGI();
	for (int i = 0; i <= n; i++)
	{
		for (int j = 0; j <= m; j++)
		{
			b[i][j] = 0;
		}
	}

	while (sgen--)
	{
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= m; j++)
			{
				b[i][j] = a[i - 1][j - 1] + a[i - 1][j] + a[i - 1][j + 1] + a[i][j - 1] + a[i][j + 1] + a[i + 1][j - 1] + a[i + 1][j] + a[i + 1][j + 1];
				if (a[i][j] == 0)
					b[i][j] = b[i][j] == birth ? 1 : 0;
				else
					b[i][j] = (survive <= b[i][j] && b[i][j] < death) ? 1 : 0;
			}
		}

		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= m; j++)
				a[i][j] = b[i][j];
		}

		system("cls");
		for (int i = 1; i <= n; i++, puts(""))
		{
			for (int j = 1; j <= m; j++)
			{
				if (b[i][j])
					printf("■");
				else
					printf("□");
			}
		}
		printf("%d세대, 간격%dms\n", gen, interval);
		gen++;
		Sleep(interval);
	}
	return 0;
}
