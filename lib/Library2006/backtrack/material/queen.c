/************************************************************************/
/*      ����������      ñ��С������                                  */
/*                                                                      */
/*      ��ħ    ��������Ȥꤢ�������Ѥˤ�������                        */
/*              �������� -p ͭ��                                        */
/*                                                                      */
/*      usage:  queen [-p] [size]                                       */
/*                                                                      */
/************************************************************************/
#include <stdio.h>

#define MAXBOARDSIZE 20
int     boardsize = 8;

int     answercount;
int     printflag;
typedef char Board[MAXBOARDSIZE][MAXBOARDSIZE];
Board   board;

#define QUEEN   'Q'
#define BLANK   '.'

#define TRUE    1
#define FALSE   0

void    initboard( void );
void    copyboard( Board dest, Board sr );
void    rotate( Board dest, Board src );
void    lrmirror( Board dest, Board src );
int     compareboard(  Board b0, Board b1 );
int     isunique( void );
void    setqueen( int x, int y );
void    setblank( int x, int y );
int     ison( int x, int y );
int     isokleft( int x, int y );
int     isokleftup( int x, int y );
int     isokleftdown( int x, int y );
int     isok( int x, int y );
void    tryqueen( int x, int y );
void    foundanswer( void );
void    printboard( Board b);
int     main( int argc, char **argv );

/*----------------------------------------------------------------------*/
/*      �������פν����                                                */
/*----------------------------------------------------------------------*/
void    initboard( void )
{
        int     x, y;

        for( x=0; x<boardsize; ++x ) {
                for( y=0; y<boardsize; ++y ) {
                        board[x][y] = BLANK;
                }
        }
}

/*----------------------------------------------------------------------*/
/*      �������פΥ��ԡ�                                                */
/*----------------------------------------------------------------------*/
void    copyboard( Board dest, Board src )
{
        int     x, y;

        for( x=0; x<boardsize; ++x )
                for( y=0; y<boardsize; ++y )
                        dest[x][y] = src[x][y];
}

/*----------------------------------------------------------------------*/
/*      ���̾�Υ��ޤ򣹣��ٲ�ž����                                    */
/*----------------------------------------------------------------------*/
void    rotate( Board dest, Board src )
{
        Board   work;           /* to, from ��Ʊ������Ǥ�OK    */
        int     x, y;

        for( x=0; x<boardsize; ++x )
                for( y=0; y<boardsize; ++y )
                        work[y][boardsize-1-x] = src[x][y];

        copyboard( dest, work );
}

/*----------------------------------------------------------------------*/
/*      ���̾�Υ��ޤ򺸱�ȿž����                                      */
/*----------------------------------------------------------------------*/
void    lrmirror( Board dest, Board src )
{
        Board   work;           /* to, from ��Ʊ������Ǥ�OK    */
        int     x, y;

        for( x=0; x<boardsize; ++x )
                for( y=0; y<boardsize; ++y )
                        work[boardsize-1-x][y] = src[x][y];

        copyboard( dest, work );
}

/*----------------------------------------------------------------------*/
/*      �׾�ξ��֤ˤ���羮���                                        */
/*----------------------------------------------------------------------*/
int     compareboard( Board b0, Board b1 )
{
        int     x, y;

        for( x=0; x<boardsize; ++x ) {
                for( y=0; y<boardsize; ++y ) {
                        if( b0[x][y] == b1[x][y] )
                                 continue;
                        return (b0[x][y] == QUEEN) ? -1 : 1;
                }
        }
        return  0;
}

/*----------------------------------------------------------------------*/
/*      ��ž��ȿž�ʤɤˤ���ˡ������Υ����å�                        */
/*----------------------------------------------------------------------*/
int     isunique( void )
{
        Board   work;

        copyboard( work, board );               /* ����board�Ϥ��Τޤ�  */

        rotate( work, work );                   /*  90�ٲ�ž    */
        if( compareboard( board, work ) > 0 )
                return  FALSE;
                
        rotate( work, work );                   /* 180�ٲ�ž    */
        if( compareboard( board, work ) > 0 )
                return  FALSE;
                
        rotate( work, work );                   /* 270�ٲ�ž    */
        if( compareboard( board, work ) > 0 )
                return  FALSE;

        lrmirror( work, board );                /* ����΢�֤�   */
        if( compareboard( board, work ) > 0 )
                return  FALSE;

        rotate( work, work );                   /*  90�ٲ�ž    */
        if( compareboard( board, work ) > 0 )
                return  FALSE;

        rotate( work, work );                   /* 180�ٲ�ž    */
        if( compareboard( board, work ) > 0 )
                return  FALSE;

        rotate( work, work );                   /* 270�ٲ�ž    */
        if( compareboard( board, work ) > 0 )
                return  FALSE;

        return  TRUE;
}

/*----------------------------------------------------------------------*/
/*      �������פλ�����˥�������򥻥å�                            */
/*----------------------------------------------------------------------*/
void    setqueen( int x, int y )
{
        board[x][y] = QUEEN;
}

/*----------------------------------------------------------------------*/
/*      �������פλ������֥�󥯤ˤ���                              */
/*----------------------------------------------------------------------*/
void    setblank( int x, int y )
{
        board[x][y] = BLANK;
}

/*----------------------------------------------------------------------*/
/*      �������(x,y)���׾夫�ɤ�����Ƚ��                               */
/*----------------------------------------------------------------------*/
int     ison( int x, int y )
{
        if( x<0 || x>=boardsize )
                return  FALSE;
        if( y<0 || y>=boardsize )
                return  FALSE;

        return  TRUE;
}

/*----------------------------------------------------------------------*/
/*      Ʊ��y��ɸ (��) �ΤȤ����¾�Υ������󤬤ʤ����Ȥ��ǧ           */
/*----------------------------------------------------------------------*/
int     isokleft( int x, int y )
{
        int     i;
        int     stat = TRUE;

        for(;;) {
                --x;
                if( ! ison( x, y ) )
                        break;

                if( board[x][y] == QUEEN ) {
                        stat = FALSE;
                        break;
                }
        }

        return stat;
}

/*----------------------------------------------------------------------*/
/*      �����г����� (��) �ΤȤ����¾�Υ������󤬤ʤ����Ȥ��ǧ        */
/*----------------------------------------------------------------------*/
int     isokleftup( int x, int y )
{
        int     i;
        int     stat = TRUE;

        for(;;) {
                --x;
                --y;
                if( ! ison( x, y ) )
                        break;

                if( board[x][y] == QUEEN ) {
                        stat = FALSE;
                        break;
                }
        }

        return stat;
}

/*----------------------------------------------------------------------*/
/*      �����г����� (��) �ΤȤ����¾�Υ������󤬤ʤ����Ȥ��ǧ        */
/*----------------------------------------------------------------------*/
int     isokleftdown( int x, int y )
{
        int     i;
        int     stat = TRUE;

        for(;;) {
                --x;
                ++y;
                if( ! ison( x, y ) )
                        break;

                if( board[x][y] == QUEEN ) {
                        stat = FALSE;
                        break;
                }
        }

        return stat;
}

/*----------------------------------------------------------------------*/
/*      �����г����� (��) �ΤȤ����¾�Υ������󤬤ʤ����Ȥ��ǧ        */
/*----------------------------------------------------------------------*/
int     isok( int x, int y )
{
        if( ! isokleft( x, y ) ) {      /* ������(��)�ˤ���Τ��֤��ʤ� */
                return  FALSE;
        }

        if( ! isokleftup( x, y ) ) {    /* ������(��)�ˤ���Τ��֤��ʤ� */
                return  FALSE;
        }

        if( ! isokleftdown( x, y ) ) {  /* ������(��)�ˤ���Τ��֤��ʤ� */
                return  FALSE;
        }

        return  TRUE;
}

/*----------------------------------------------------------------------*/
/*      �������פλ������˥���������֤��뤫Ĵ�٤�                  */
/*----------------------------------------------------------------------*/
void    tryqueen( int x, int y )
{
        int     z;

        if( ! isok( x, y ) )
                return;

        setqueen( x, y );               /* �֤��� */

        if( x == boardsize-1 ) {        /* �����֤������� */
                foundanswer();
        } else {                        /* ��ı�¦�ˤĤ���Ĵ�٤� */    
                for( z=0; z<boardsize; ++z ) {
                        tryqueen( x+1, z );
                }
        }

        setblank( x, y );               /* ������ */
}

/*----------------------------------------------------------------------*/
/*      �򤬸��Ĥ��ä�                                                  */
/*----------------------------------------------------------------------*/
void    foundanswer( void )
{
        if( ! isunique() )
                return;

        ++answercount;

        if( printflag ) {
                printf( "Answer %d\n", answercount );
                printboard( board );
        }
}

/*----------------------------------------------------------------------*/
/*      �������פΥץ���                                              */
/*----------------------------------------------------------------------*/
void    printboard( Board b )
{
        int     x, y;

        for( y=0; y<boardsize; ++y ) {
                for( x=0; x<boardsize; ++x ) {
                        printf( " %c", b[x][y] );
                }
                printf( "\n" );
        }
        printf( "\n" );
}

/*----------------------------------------------------------------------*/
/*      �ᥤ��                                                          */
/*----------------------------------------------------------------------*/
int     main( int argc, char **argv )
{
        int     y;

        printflag = TRUE;

        for( ++argv, --argc; argc>0; ++argv, --argc ) {
                if( isdigit( **argv ) ) {
                        boardsize = atoi( *argv );
                        continue;
                }
                if( strcmp(*argv,"-p") == 0 ) {
                        printflag = FALSE;
                }
        }

        answercount = 0;
        initboard();

        for( y=0; y<boardsize; ++y ) {
                tryqueen( 0, y );
        }

        printf( "Total count %d\n", answercount );
}

/************************************************************************/
/*                              End                                     */
/************************************************************************/
