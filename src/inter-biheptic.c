/*
 * libinter - Interpolation methods library
 *
 * Copyright (c) 2013-2015 FOXEL SA - http://foxel.ch
 * Please read <http://foxel.ch/license> for more information.
 *
 *
 * Author(s):
 *
 *      Nils Hamel <n.hamel@foxel.ch>
 *
 *
 * This file is part of the FOXEL project <http://foxel.ch>.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *
 * Additional Terms:
 *
 *      You are required to preserve legal notices and author attributions in
 *      that material or in the Appropriate Legal Notices displayed by works
 *      containing it.
 *
 *      You are required to attribute the work as explained in the "Usage and
 *      Attribution" section of <http://foxel.ch/license>.
 */


/* 
    Source - Includes
 */

    # include "inter-bipentic.h"

/*
    Source - Fast biheptic image pixel interpolation method
 */

    li_C8_t li_bihepticf(

        li_C8_t   const * const liBytes, 
        li_Size_t               liWidth,
        li_Size_t const         liHeight,
        li_Size_t const         liLayer, 
        li_Size_t const         liChannel,
        li_Real_t const         liX,
        li_Real_t const         liY

    ) {

        /* Interpolation vectors variables */
        li_Real_t liVS[64] = { li_Real_s( 0.0 ) };
        li_Real_t liVC[64] = { li_Real_s( 0.0 ) };

        /* Optimization variables */
        li_Real_t liTX1 = li_Real_s( 0.0 );
        li_Real_t liTY1 = li_Real_s( 0.0 );
        li_Real_t liTX2 = li_Real_s( 0.0 );
        li_Real_t liTY2 = li_Real_s( 0.0 );
        li_Real_t liTX3 = li_Real_s( 0.0 );
        li_Real_t liTY3 = li_Real_s( 0.0 );
        li_Real_t liTX4 = li_Real_s( 0.0 );
        li_Real_t liTY4 = li_Real_s( 0.0 );
        li_Real_t liTX5 = li_Real_s( 0.0 );
        li_Real_t liTY5 = li_Real_s( 0.0 );
        li_Real_t liTX6 = li_Real_s( 0.0 );
        li_Real_t liTY6 = li_Real_s( 0.0 );
        li_Real_t liTX7 = li_Real_s( 0.0 );
        li_Real_t liTY7 = li_Real_s( 0.0 );

        /* Interpolation reference variables */
        li_Size_t liPXrf = li_Size_s( 0 );
        li_Size_t liPYrf = li_Size_s( 0 );
        li_Size_t liPXmm = li_Size_s( 0 );
        li_Size_t liPYmm = li_Size_s( 0 );

        /* Interpolation sampling variables */
        li_Size_t liPXm3 = li_Size_s( 0 );
        li_Size_t liPXm2 = li_Size_s( 0 );
        li_Size_t liPXm1 = li_Size_s( 0 );
        li_Size_t liPXp1 = li_Size_s( 0 );
        li_Size_t liPXp2 = li_Size_s( 0 );
        li_Size_t liPXp3 = li_Size_s( 0 );
        li_Size_t liPXp4 = li_Size_s( 0 );
        li_Size_t liPYm3 = li_Size_s( 0 );
        li_Size_t liPYm2 = li_Size_s( 0 );
        li_Size_t liPYm1 = li_Size_s( 0 );
        li_Size_t liPYp1 = li_Size_s( 0 );
        li_Size_t liPYp2 = li_Size_s( 0 );
        li_Size_t liPYp3 = li_Size_s( 0 );
        li_Size_t liPYp4 = li_Size_s( 0 );

        /* Interpolated variables */
        li_Real_t liIV = li_Real_s( 0.0 );

        /* Compute relatlive grid parameters */
        liPXrf = li_Floor( liX );
        liPYrf = li_Floor( liY );

        /* Memorize reference point */
        liPXmm = liPXrf;
        liPYmm = liPYrf;

        /* Compute sampling nodes */
        liPXm3 = liPXrf - li_Size_s( 3 );
        liPXm2 = liPXrf - li_Size_s( 2 );
        liPXm1 = liPXrf - li_Size_s( 1 );
        liPYm3 = liPYrf - li_Size_s( 3 );
        liPYm2 = liPYrf - li_Size_s( 2 );
        liPYm1 = liPYrf - li_Size_s( 1 );
        liPXp1 = liPXrf + li_Size_s( 1 );
        liPXp2 = liPXrf + li_Size_s( 2 );
        liPXp3 = liPXrf + li_Size_s( 3 );
        liPXp4 = liPXrf + li_Size_s( 4 );
        liPYp1 = liPYrf + li_Size_s( 1 );
        liPYp2 = liPYrf + li_Size_s( 2 );
        liPYp3 = liPYrf + li_Size_s( 3 );
        liPYp4 = liPYrf + li_Size_s( 4 );

        /* Boundaries analysis */
        if ( liPXm3 < li_Size_s( 0 ) ) {

            /* Boundary condition correction */
            liPXm3 = li_Size_s( 0 );

            /* Boundaries analysis */
            if ( liPXm2 < li_Size_s( 0 ) ) {

                /* Boundary condition correction */
                liPXm2 = li_Size_s( 0 );

                /* Boundaries analysis */
                if ( liPXm1 < li_Size_s( 0 ) ) {

                    /* Boundary condition correction */
                    liPXm1 = li_Size_s( 0 );

                    /* Boundaries analysis */
                    if ( liPXrf < li_Size_s( 0 ) ) {

                        /* Boundary condition correction */
                        liPXrf = li_Size_s( 0 );

                        /* Boundaries analysis */
                        if ( liPXp1 < li_Size_s( 0 ) ) {

                            /* Boundary condition correction */
                            liPXp1 = li_Size_s( 0 );

                            /* Boundaries analysis */
                            if ( liPXp2 < li_Size_s( 0 ) ) {

                                /* Boundary condition correction */
                                liPXp2 = li_Size_s( 0 );

                                /* Boundaries analysis */
                                if ( liPXp3 < li_Size_s( 0 ) ) {

                                    /* Boundary condition correction */
                                    liPXp3 = li_Size_s( 0 );

                                    /* Boundaries analysis */
                                    if ( liPXp4 < li_Size_s( 0 ) ) {

                                        /* Boundary condition correction */
                                        liPXp4 = li_Size_s( 0 );

                                    }

                                }

                            }

                        }

                    }

                }

            }

        } else
        if ( liPXp4 >= liWidth ) {

            /* Boundary condition correction */
            liPXp4 = liWidth - li_Size_s( 1 );

            /* Boundaries analysis */
            if ( liPXp3 >= liWidth ) {

                /* Boundary condition correction */
                liPXp3 = liPXp4;

                /* Boundaries analysis */
                if ( liPXp2 >= liWidth ) {

                    /* Boundary condition correction */
                    liPXp2 = liPXp4;

                    /* Boundaries analysis */
                    if ( liPXp1 >= liWidth ) {

                        /* Boundary condition correction */
                        liPXp1 = liPXp4;

                        /* Boundaries analysis */
                        if ( liPXrf >= liWidth ) {

                            /* Boundary condition correction */
                            liPXrf = liPXp4;

                            /* Boundaries analysis */
                            if ( liPXm1 >= liWidth ) {

                                /* Boundary condition correction */
                                liPXm1 = liPXp4;

                                /* Boundaries analysis */
                                if ( liPXm2 >= liWidth ) {

                                    /* Boundary condition correction */
                                    liPXm2 = liPXp4;

                                    /* Boundaries analysis */
                                    if ( liPXm3 >= liWidth ) {

                                        /* Boundary condition correction */
                                        liPXm3 = liPXp4;

                                    }

                                }

                            }

                        }

                    }

                }

            }

        }

        /* Boundaries analysis */
        if ( liPYm3 < li_Size_s( 0 ) ) {

            /* Boundary condition correction */
            liPYm3 = li_Size_s( 0 );

            /* Boundaries analysis */
            if ( liPYm2 < li_Size_s( 0 ) ) {

                /* Boundary condition correction */
                liPYm2 = li_Size_s( 0 );

                /* Boundaries analysis */
                if ( liPYm1 < li_Size_s( 0 ) ) {

                    /* Boundary condition correction */
                    liPYm1 = li_Size_s( 0 );

                    /* Boundaries analysis */
                    if ( liPYrf < li_Size_s( 0 ) ) {

                        /* Boundary condition correction */
                        liPYrf = li_Size_s( 0 );

                        /* Boundaries analysis */
                        if ( liPYp1 < li_Size_s( 0 ) ) {

                            /* Boundary condition correction */
                            liPYp1 = li_Size_s( 0 );

                            /* Boundaries analysis */
                            if ( liPYp2 < li_Size_s( 0 ) ) {

                                /* Boundary condition correction */
                                liPYp2 = li_Size_s( 0 );

                                /* Boundaries analysis */
                                if ( liPYp3 < li_Size_s( 0 ) ) {

                                    /* Boundary condition correction */
                                    liPYp3 = li_Size_s( 0 );

                                    /* Boundaries analysis */
                                    if ( liPYp4 < li_Size_s( 0 ) ) {

                                        /* Boundary condition correction */
                                        liPYp4 = li_Size_s( 0 );

                                    }

                                }

                            }

                        }

                    }

                }

            }

        } else
        if ( liPYp4 >= liHeight ) {

            /* Boundary condition correction */
            liPYp4 = liHeight - li_Size_s( 1 );

            /* Boundaries analysis */
            if ( liPYp3 >= liHeight ) {

                /* Boundary condition correction */
                liPYp3 = liPYp4;

                /* Boundaries analysis */
                if ( liPYp2 >= liHeight ) {

                    /* Boundary condition correction */
                    liPYp2 = liPYp4;

                    /* Boundaries analysis */
                    if ( liPYp1 >= liHeight ) {

                        /* Boundary condition correction */
                        liPYp1 = liPYp4;

                        /* Boundaries analysis */
                        if ( liPYrf >= liHeight ) {

                            /* Boundary condition correction */
                            liPYrf = liPYp4;

                            /* Boundaries analysis */
                            if ( liPYm1 >= liHeight ) {

                                /* Boundary condition correction */
                                liPYm1 = liPYp4;

                                /* Boundaries analysis */
                                if ( liPYm2 >= liHeight ) {

                                    /* Boundary condition correction */
                                    liPYm2 = liPYp4;

                                    /* Boundaries analysis */
                                    if ( liPYm3 >= liHeight ) {

                                        /* Boundary condition correction */
                                        liPYm3 = liPYp4;

                                    }

                                }

                            }

                        }

                    }

                }

            }

        }

        /* Compute memory width */
        liWidth *= liLayer; if ( liWidth % li_Size_s( 4 ) ) liWidth += li_Size_s( 4 ) - liWidth % li_Size_s( 4 );

        /* Compute interpolation vector */
        liVS[ 0] = * ( liBytes + liWidth * liPYm3 + liLayer * liPXm3 + liChannel );
        liVS[ 1] = * ( liBytes + liWidth * liPYm3 + liLayer * liPXm2 + liChannel );
        liVS[ 2] = * ( liBytes + liWidth * liPYm3 + liLayer * liPXm1 + liChannel );
        liVS[ 3] = * ( liBytes + liWidth * liPYm3 + liLayer * liPXrf + liChannel );
        liVS[ 4] = * ( liBytes + liWidth * liPYm3 + liLayer * liPXp1 + liChannel );
        liVS[ 5] = * ( liBytes + liWidth * liPYm3 + liLayer * liPXp2 + liChannel );
        liVS[ 6] = * ( liBytes + liWidth * liPYm3 + liLayer * liPXp3 + liChannel );
        liVS[ 7] = * ( liBytes + liWidth * liPYm3 + liLayer * liPXp4 + liChannel );
        liVS[ 8] = * ( liBytes + liWidth * liPYm2 + liLayer * liPXm3 + liChannel );
        liVS[ 9] = * ( liBytes + liWidth * liPYm2 + liLayer * liPXm2 + liChannel );
        liVS[10] = * ( liBytes + liWidth * liPYm2 + liLayer * liPXm1 + liChannel );
        liVS[11] = * ( liBytes + liWidth * liPYm2 + liLayer * liPXrf + liChannel );
        liVS[12] = * ( liBytes + liWidth * liPYm2 + liLayer * liPXp1 + liChannel );
        liVS[13] = * ( liBytes + liWidth * liPYm2 + liLayer * liPXp2 + liChannel );
        liVS[14] = * ( liBytes + liWidth * liPYm2 + liLayer * liPXp3 + liChannel );
        liVS[15] = * ( liBytes + liWidth * liPYm2 + liLayer * liPXp4 + liChannel );
        liVS[16] = * ( liBytes + liWidth * liPYm1 + liLayer * liPXm3 + liChannel );
        liVS[17] = * ( liBytes + liWidth * liPYm1 + liLayer * liPXm2 + liChannel );
        liVS[18] = * ( liBytes + liWidth * liPYm1 + liLayer * liPXm1 + liChannel );
        liVS[19] = * ( liBytes + liWidth * liPYm1 + liLayer * liPXrf + liChannel );
        liVS[20] = * ( liBytes + liWidth * liPYm1 + liLayer * liPXp1 + liChannel );
        liVS[21] = * ( liBytes + liWidth * liPYm1 + liLayer * liPXp2 + liChannel );
        liVS[22] = * ( liBytes + liWidth * liPYm1 + liLayer * liPXp3 + liChannel );
        liVS[23] = * ( liBytes + liWidth * liPYm1 + liLayer * liPXp4 + liChannel );
        liVS[24] = * ( liBytes + liWidth * liPYrf + liLayer * liPXm3 + liChannel );
        liVS[25] = * ( liBytes + liWidth * liPYrf + liLayer * liPXm2 + liChannel );
        liVS[26] = * ( liBytes + liWidth * liPYrf + liLayer * liPXm1 + liChannel );
        liVS[27] = * ( liBytes + liWidth * liPYrf + liLayer * liPXrf + liChannel );
        liVS[28] = * ( liBytes + liWidth * liPYrf + liLayer * liPXp1 + liChannel );
        liVS[29] = * ( liBytes + liWidth * liPYrf + liLayer * liPXp2 + liChannel );
        liVS[30] = * ( liBytes + liWidth * liPYrf + liLayer * liPXp3 + liChannel );
        liVS[31] = * ( liBytes + liWidth * liPYrf + liLayer * liPXp4 + liChannel );
        liVS[32] = * ( liBytes + liWidth * liPYp1 + liLayer * liPXm3 + liChannel );
        liVS[33] = * ( liBytes + liWidth * liPYp1 + liLayer * liPXm2 + liChannel );
        liVS[34] = * ( liBytes + liWidth * liPYp1 + liLayer * liPXm1 + liChannel );
        liVS[35] = * ( liBytes + liWidth * liPYp1 + liLayer * liPXrf + liChannel );
        liVS[36] = * ( liBytes + liWidth * liPYp1 + liLayer * liPXp1 + liChannel );
        liVS[37] = * ( liBytes + liWidth * liPYp1 + liLayer * liPXp2 + liChannel );
        liVS[38] = * ( liBytes + liWidth * liPYp1 + liLayer * liPXp3 + liChannel );
        liVS[39] = * ( liBytes + liWidth * liPYp1 + liLayer * liPXp4 + liChannel );
        liVS[40] = * ( liBytes + liWidth * liPYp2 + liLayer * liPXm3 + liChannel );
        liVS[41] = * ( liBytes + liWidth * liPYp2 + liLayer * liPXm2 + liChannel );
        liVS[42] = * ( liBytes + liWidth * liPYp2 + liLayer * liPXm1 + liChannel );
        liVS[43] = * ( liBytes + liWidth * liPYp2 + liLayer * liPXrf + liChannel );
        liVS[44] = * ( liBytes + liWidth * liPYp2 + liLayer * liPXp1 + liChannel );
        liVS[45] = * ( liBytes + liWidth * liPYp2 + liLayer * liPXp2 + liChannel );
        liVS[46] = * ( liBytes + liWidth * liPYp2 + liLayer * liPXp3 + liChannel );
        liVS[47] = * ( liBytes + liWidth * liPYp2 + liLayer * liPXp4 + liChannel );
        liVS[48] = * ( liBytes + liWidth * liPYp3 + liLayer * liPXm3 + liChannel );
        liVS[49] = * ( liBytes + liWidth * liPYp3 + liLayer * liPXm2 + liChannel );
        liVS[50] = * ( liBytes + liWidth * liPYp3 + liLayer * liPXm1 + liChannel );
        liVS[51] = * ( liBytes + liWidth * liPYp3 + liLayer * liPXrf + liChannel );
        liVS[52] = * ( liBytes + liWidth * liPYp3 + liLayer * liPXp1 + liChannel );
        liVS[53] = * ( liBytes + liWidth * liPYp3 + liLayer * liPXp2 + liChannel );
        liVS[54] = * ( liBytes + liWidth * liPYp3 + liLayer * liPXp3 + liChannel );
        liVS[55] = * ( liBytes + liWidth * liPYp3 + liLayer * liPXp4 + liChannel );
        liVS[56] = * ( liBytes + liWidth * liPYp4 + liLayer * liPXm3 + liChannel );
        liVS[57] = * ( liBytes + liWidth * liPYp4 + liLayer * liPXm2 + liChannel );
        liVS[58] = * ( liBytes + liWidth * liPYp4 + liLayer * liPXm1 + liChannel );
        liVS[59] = * ( liBytes + liWidth * liPYp4 + liLayer * liPXrf + liChannel );
        liVS[60] = * ( liBytes + liWidth * liPYp4 + liLayer * liPXp1 + liChannel );
        liVS[61] = * ( liBytes + liWidth * liPYp4 + liLayer * liPXp2 + liChannel );
        liVS[62] = * ( liBytes + liWidth * liPYp4 + liLayer * liPXp3 + liChannel );
        liVS[63] = * ( liBytes + liWidth * liPYp4 + liLayer * liPXp4 + liChannel );

        /* Compute interpolation matrix product */
        liVC[ 0] = ( li_Real_s(     73209999932589693839616245760.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 0];
        liVC[ 1] = ( li_Real_s(   -189823071253798757448923742208.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 0] +
                   ( li_Real_s(    512469999528217409900372819968.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 8] +
                   ( li_Real_s(   -768704999292465339410914738176.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[16] +
                   ( li_Real_s(    854116665880673825351933100032.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[24] +
                   ( li_Real_s(   -640587499410621829285563858944.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[32] +
                   ( li_Real_s(    307481999717153148941797163008.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[40] +
                   ( li_Real_s(    -85411666588112714080192561152.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[48] +
                   ( li_Real_s(     10458571418954253832468561920.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[56];
        liVC[ 2] = ( li_Real_s(    190752722046615177223569670144.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 0] +
                   ( li_Real_s(   -816291499248611949703646412800.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 8] +
                   ( li_Real_s(   1608789748519365007824436330496.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[16] +
                   ( li_Real_s(  -1929896942668604408664426545152.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[24] +
                   ( li_Real_s(   1500804998619248484179064651776.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[32] +
                   ( li_Real_s(   -735760499323213694821317214208.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[40] +
                   ( li_Real_s(    207224972031639005135437299712.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[48] +
                   ( li_Real_s(    -25623499976437836677396824064.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[56];
        liVC[ 3] = ( li_Real_s(    -98325097131716311045508169728.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 0] +
                   ( li_Real_s(    518977555077894736229131354112.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 8] +
                   ( li_Real_s(  -1198508707230368218269146415104.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[16] +
                   ( li_Real_s(   1582149442988612520693016297472.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[24] +
                   ( li_Real_s(  -1293885068254023762728703754240.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[32] +
                   ( li_Real_s(    654009332731701189836504301568.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[40] +
                   ( li_Real_s(   -188007347049293601689833570304.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[48] +
                   ( li_Real_s(     23589888867193587712028311552.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[56];
        liVC[ 4] = ( li_Real_s(     28470555529353211352283348992.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 0] +
                   ( li_Real_s(   -169298124844197603172021174272.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 8] +
                   ( li_Real_s(    433159166268066180717281804288.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[16] +
                   ( li_Real_s(   -619742985540860595102793334784.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[24] +
                   ( li_Real_s(    536873332839378239395465265152.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[32] +
                   ( li_Real_s(   -282163541407082840317017194496.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[40] +
                   ( li_Real_s(     83378055478856330904499912704.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[48] +
                   ( li_Real_s(    -10676458323512851209931194368.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[56];
        liVC[ 5] = ( li_Real_s(     -4677305551251581686874374144.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 0] +
                   ( li_Real_s(     29995763861287533871821225984.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 8] +
                   ( li_Real_s(    -82361249924215604884096942080.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[16] +
                   ( li_Real_s(    125575485995567933368444125184.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[24] +
                   ( li_Real_s(   -114899027672062842511581773824.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[32] +
                   ( li_Real_s(     63143624941906291808163332096.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[40] +
                   ( li_Real_s(    -19319305537782148345842630656.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[48] +
                   ( li_Real_s(      2542013886550389792664715264.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[56];
        liVC[ 6] = ( li_Real_s(       406722221848022864122347520.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 0] +
                   ( li_Real_s(     -2745374997474079445776072704.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 8] +
                   ( li_Real_s(      7931083326036157675260084224.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[16] +
                   ( li_Real_s(    -12710069432750261212974940160.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[24] +
                   ( li_Real_s(     12201666655440310577888493568.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[32] +
                   ( li_Real_s(     -7015958326878227400602157056.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[40] +
                   ( li_Real_s(      2236972220164090052904747008.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[48] +
                   ( li_Real_s(      -305041666386014863169159168.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[56];
        liVC[ 7] = ( li_Real_s(       -14525793637431556656070656.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 0] +
                   ( li_Real_s(       101680555462013962367795200.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 8] +
                   ( li_Real_s(      -305041666386028057308692480.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[16] +
                   ( li_Real_s(       508402777310030006082076672.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[24] +
                   ( li_Real_s(      -508402777310015918589345792.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[32] +
                   ( li_Real_s(       305041666386001772108840960.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[40] +
                   ( li_Real_s(      -101680555461998070988800000.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[48] +
                   ( li_Real_s(        14525793637427935998640128.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[56];
        liVC[ 8] = ( li_Real_s(   -189823071271450686557146578944.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 0] +
                   ( li_Real_s(    512469999644054495915969347584.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 1] +
                   ( li_Real_s(   -768704999620760441535156191232.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 2] +
                   ( li_Real_s(    854116666398434519374721187840.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 3] +
                   ( li_Real_s(   -640587499900052348377401131008.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 4] +
                   ( li_Real_s(    307481999994352802231195009024.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 5] +
                   ( li_Real_s(    -85411666675279321917995089920.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 6] +
                   ( li_Real_s(     10458571430700954477534380032.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 7] +
                   ( li_Real_s(             112773055446154051584.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 8] +
                   ( li_Real_s(            -742068659744058900480.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 9] +
                   ( li_Real_s(            2105203681952618774528.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[10] +
                   ( li_Real_s(           -3319830182780050866176.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[11] +
                   ( li_Real_s(            3135967199382173908992.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[12] +
                   ( li_Real_s(           -1774420349856495960064.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[13] +
                   ( li_Real_s(             557431158959882698752.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[14] +
                   ( li_Real_s(             -75055903360222134272.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[15] +
                   ( li_Real_s(            -306507611938496380928.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[16] +
                   ( li_Real_s(            2022929937524476608512.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[17] +
                   ( li_Real_s(           -5746424551825676959744.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[18] +
                   ( li_Real_s(            9063343859863808638976.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[19] +
                   ( li_Real_s(           -8556851816974244642816.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[20] +
                   ( li_Real_s(            4837537391872588120064.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[21] +
                   ( li_Real_s(           -1518278028479157501952.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[22] +
                   ( li_Real_s(             204250819956700348416.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[23] +
                   ( li_Real_s(             458619580267196383232.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[24] +
                   ( li_Real_s(           -3037154847839664734208.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[25] +
                   ( li_Real_s(            8642696820762041384960.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[26] +
                   ( li_Real_s(          -13639255915932424339456.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[27] +
                   ( li_Real_s(           12874591427000476368896.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[28] +
                   ( li_Real_s(           -7274116112808185692160.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[29] +
                   ( li_Real_s(            2281280682744560746496.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[30] +
                   ( li_Real_s(            -306661634193993957376.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[31] +
                   ( li_Real_s(            -408479303003805581312.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[32] +
                   ( li_Real_s(            2715388006598145736704.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[33] +
                   ( li_Real_s(           -7744242657185015791616.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[34] +
                   ( li_Real_s(           12233717514029368344576.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[35] +
                   ( li_Real_s(          -11549867303532117360640.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[36] +
                   ( li_Real_s(            6523585493143097704448.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[37] +
                   ( li_Real_s(           -2044808813946246791168.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[38] +
                   ( li_Real_s(             274707063896573870080.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[39] +
                   ( li_Real_s(             217212733757215211520.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[40] +
                   ( li_Real_s(           -1449856145701475975168.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[41] +
                   ( li_Real_s(            4145695713767052017664.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[42] +
                   ( li_Real_s(           -6558006210830171897856.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[43] +
                   ( li_Real_s(            6194453501977281167360.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[44] +
                   ( li_Real_s(           -3498541624050126422016.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[45] +
                   ( li_Real_s(            1096249617293987807232.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[46] +
                   ( li_Real_s(            -147207586213762465792.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[47] +
                   ( li_Real_s(             -64094381844896571392.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[48] +
                   ( li_Real_s(             429616134215840890880.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[49] +
                   ( li_Real_s(           -1231859777255293059072.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[50] +
                   ( li_Real_s(            1951751228620783747072.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[51] +
                   ( li_Real_s(           -1844834391147982618624.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[52] +
                   ( li_Real_s(            1042061202932667908096.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[53] +
                   ( li_Real_s(            -326463522546558369792.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[54] +
                   ( li_Real_s(              43823507025438212096.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[55] +
                   ( li_Real_s(               8130742215982382080.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[56] +
                   ( li_Real_s(             -54719615920851656704.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[57] +
                   ( li_Real_s(             157331313853469523968.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[58] +
                   ( li_Real_s(            -249679409583075622912.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[59] +
                   ( li_Real_s(             236182323764560822272.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[60] +
                   ( li_Real_s(            -133434805833779527680.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[61] +
                   ( li_Real_s(              41798502529387847680.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[62] +
                   ( li_Real_s(              -5609051025692888064.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[63];
        liVC[ 9] = ( li_Real_s(    492184106201119091582459445248.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 0] +
                   ( li_Real_s(  -1328761498903215916640498614272.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 1] +
                   ( li_Real_s(   1993142248512438039969693433856.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 2] +
                   ( li_Real_s(  -2214602498515637949978627801088.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 3] +
                   ( li_Real_s(   1660951874006256318762941677568.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 4] +
                   ( li_Real_s(   -797256899572123107342998831104.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 5] +
                   ( li_Real_s(    221460249891127411069354508288.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 6] +
                   ( li_Real_s(    -27117581619963583957114552320.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 7] +
                   ( li_Real_s(  -1328761499022761153999281324032.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 8] +
                   ( li_Real_s(   3587289998267544323767119380480.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 9] +
                   ( li_Real_s(  -5380934999517532336329194471424.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[10] +
                   ( li_Real_s(   5978816668347680930267412824064.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[11] +
                   ( li_Real_s(  -4484112502789324913951589269504.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[12] +
                   ( li_Real_s(   2152374001972449301077669445632.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[13] +
                   ( li_Real_s(   -597881667354337432659881361408.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[14] +
                   ( li_Real_s(     73210000096282557261232996352.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[15] +
                   ( li_Real_s(   1993142249071829868210406031360.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[16] +
                   ( li_Real_s(  -5380935000979182350791730003968.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[17] +
                   ( li_Real_s(   8071402509621303287544257970176.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[18] +
                   ( li_Real_s(  -8968225019168197527198960189440.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[19] +
                   ( li_Real_s(   6726168770165145756640410075136.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[20] +
                   ( li_Real_s(  -3228561012079388827502671560704.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[21] +
                   ( li_Real_s(    896822503894664756647266615296.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[22] +
                   ( li_Real_s(   -109815000526176019080141602816.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[23] +
                   ( li_Real_s(  -2214602499592303942744884117504.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[24] +
                   ( li_Real_s(   5978816671963989240352721600512.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[25] +
                   ( li_Real_s(  -8968225022927138215182813102080.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[26] +
                   ( li_Real_s(   9964694485451663466039412260864.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[27] +
                   ( li_Real_s(  -7473520874647209212643528146944.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[28] +
                   ( li_Real_s(   3587290024204293617650860294144.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[29] +
                   ( li_Real_s(   -996469452156435860541161865216.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[30] +
                   ( li_Real_s(    122016667703140045052276899840.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[31] +
                   ( li_Real_s(   1660951875117104914175916769280.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[32] +
                   ( li_Real_s(  -4484112506855694260348680929280.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[33] +
                   ( li_Real_s(   6726168775612265268543720783872.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[34] +
                   ( li_Real_s(  -7473520877664927207756421660672.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[35] +
                   ( li_Real_s(   5605140669009642517352559935488.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[36] +
                   ( li_Real_s(  -2690467525575451184832500989952.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[37] +
                   ( li_Real_s(    747352091444903924577534476288.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[38] +
                   ( li_Real_s(    -91512501087843690237151674368.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[39] +
                   ( li_Real_s(   -797256900226110231006861590528.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[40] +
                   ( li_Real_s(   2152374004459948378961072881664.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[41] +
                   ( li_Real_s(  -3228561015723862086707601997824.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[42] +
                   ( li_Real_s(   3587290026822460135122791301120.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[43] +
                   ( li_Real_s(  -2690467526444281121345189707776.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[44] +
                   ( li_Real_s(   1291424415305485970365726326784.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[45] +
                   ( li_Real_s(   -358729004842110611041781022720.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[46] +
                   ( li_Real_s(     43926000648467428201239412736.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[47] +
                   ( li_Real_s(    221460250100175428203894013952.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[48] +
                   ( li_Real_s(   -597881668165449165979445624832.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[49] +
                   ( li_Real_s(    896822505134601013341980721152.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[50] +
                   ( li_Real_s(   -996469453137963029704239742976.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[51] +
                   ( li_Real_s(    747352091872664542909462216704.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[52] +
                   ( li_Real_s(   -358729004930846934455954702336.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[53] +
                   ( li_Real_s(     99646946001819880436222918656.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[54] +
                   ( li_Real_s(    -12201666875001119025408245760.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[55] +
                   ( li_Real_s(    -27117581648315929440527843328.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[56] +
                   ( li_Real_s(     73210000207479299587335782400.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[57] +
                   ( li_Real_s(   -109815000699931014784838795264.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[58] +
                   ( li_Real_s(    122016667847042526006669737984.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[59] +
                   ( li_Real_s(    -91512501157077368979043909632.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[60] +
                   ( li_Real_s(     43926000667163620676965761024.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[61] +
                   ( li_Real_s(    -12201666877134149593061130240.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[62] +
                   ( li_Real_s(      1494081660778182032127688704.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[63];
        liVC[10] = ( li_Real_s(   -494594557839347178260102381568.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 0] +
                   ( li_Real_s(   1335269054055156504871892418560.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 1] +
                   ( li_Real_s(  -2002903580743431872531885195264.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 2] +
                   ( li_Real_s(   2225448422783404351035598176256.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 3] +
                   ( li_Real_s(  -1669086316953559422782148706304.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 4] +
                   ( li_Real_s(    801161432086538393159766900736.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 5] +
                   ( li_Real_s(   -222544842230885555469994164224.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 6] +
                   ( li_Real_s(     27250388842128927334732922880.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 7] +
                   ( li_Real_s(   2116527244471166182673260478464.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 8] +
                   ( li_Real_s(  -5714040494682272921862853885952.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 9] +
                   ( li_Real_s(   8571060742295128999762098913280.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[10] +
                   ( li_Real_s(  -9523400825596321750216779759616.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[11] +
                   ( li_Real_s(   7142550620035478578381522468864.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[12] +
                   ( li_Real_s(  -3428424298001278211428267851776.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[13] +
                   ( li_Real_s(    952340082849291571482652049408.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[14] +
                   ( li_Real_s(   -116613071371191657143260413952.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[15] +
                   ( li_Real_s(  -4171361991291932884351085182976.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[16] +
                   ( li_Real_s(  11261528243064728104290003976192.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[17] +
                   ( li_Real_s( -16892292370512425025898169761792.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[18] +
                   ( li_Real_s(  18769213752565435684906623565824.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[19] +
                   ( li_Real_s( -14076910320265151467737279627264.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[20] +
                   ( li_Real_s(   6756916956257754947888854597632.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[21] +
                   ( li_Real_s(  -1876921377282017403587205791744.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[22] +
                   ( li_Real_s(    229827107463607411169560625152.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[23] +
                   ( li_Real_s(   5003947074077433075020427427840.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[24] +
                   ( li_Real_s( -13509278607811686962385920196608.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[25] +
                   ( li_Real_s(  20263917926369620284259530964992.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[26] +
                   ( li_Real_s( -22515464379907379026059176443904.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[27] +
                   ( li_Real_s(  16886598297681660337011480854528.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[28] +
                   ( li_Real_s(  -8105567188338594262810875658240.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[29] +
                   ( li_Real_s(   2251546442406261363898868301824.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[30] +
                   ( li_Real_s(   -275699564477340423157215920128.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[31] +
                   ( li_Real_s(  -3891372962246000711136603799552.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[32] +
                   ( li_Real_s(  10505635001161958939630290075648.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[33] +
                   ( li_Real_s( -15758452518739971511304610381824.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[34] +
                   ( li_Real_s(  17509391706965150954707132350464.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[35] +
                   ( li_Real_s( -13132043794328842826129103388672.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[36] +
                   ( li_Real_s(   6303381027264852844578682699776.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[37] +
                   ( li_Real_s(  -1750939175568209851869881696256.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[38] +
                   ( li_Real_s(    214400715491059206036838678528.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[39] +
                   ( li_Real_s(   1907721867077713002362654687232.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[40] +
                   ( li_Real_s(  -5150323502135271495993214894080.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[41] +
                   ( li_Real_s(   7725485263899538449246587977728.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[42] +
                   ( li_Real_s(  -8583872527533049924615852261376.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[43] +
                   ( li_Real_s(   6437904404314621928630269247488.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[44] +
                   ( li_Real_s(  -3090194117729220715677522853888.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[45] +
                   ( li_Real_s(    858387255736521867844114186240.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[46] +
                   ( li_Real_s(   -105108643630848485052106407936.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[47] +
                   ( li_Real_s(   -537304749233640338660379328512.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[48] +
                   ( li_Real_s(   1450574806505170755078439567360.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[49] +
                   ( li_Real_s(  -2175862213302800889574340952064.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[50] +
                   ( li_Real_s(   2417624685425611490125747847168.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[51] +
                   ( li_Real_s(  -1813218516902695329475569123328.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[52] +
                   ( li_Real_s(    870344889304314522148773298176.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[53] +
                   ( li_Real_s(   -241762469514849556494446231552.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[54] +
                   ( li_Real_s(     29603567718887939476891369472.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[55] +
                   ( li_Real_s(     66438074983018184481878048768.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[56] +
                   ( li_Real_s(   -179364500147949489764134027264.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[57] +
                   ( li_Real_s(    269046750708150178720373538816.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[58] +
                   ( li_Real_s(   -298940834664081873988004872192.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[59] +
                   ( li_Real_s(    224205626384055438568557903872.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[60] +
                   ( li_Real_s(   -107618700825989559233135247360.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[61] +
                   ( li_Real_s(     29894083598413909439801196544.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[62] +
                   ( li_Real_s(     -3660500035594503873420591104.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[63];
        liVC[11] = ( li_Real_s(    254942930376703916667501019136.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 0] +
                   ( li_Real_s(   -688275679624028423831821484032.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 1] +
                   ( li_Real_s(   1032413519058674623233801584640.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 2] +
                   ( li_Real_s(  -1147126131971962972600778358784.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 3] +
                   ( li_Real_s(    860344598801919367365628264448.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 4] +
                   ( li_Real_s(   -412965407352683744085963440128.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 5] +
                   ( li_Real_s(    114712613132761372806134890496.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 6] +
                   ( li_Real_s(    -14046442421398318856454275072.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 7] +
                   ( li_Real_s(  -1345634660585067335006476566528.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 8] +
                   ( li_Real_s(   3632842885024186825092968218624.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 9] +
                   ( li_Real_s(  -5449264327149238633863418216448.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[10] +
                   ( li_Real_s(   6054738141358430205260591005696.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[11] +
                   ( li_Real_s(  -4541053606306012698583232413696.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[12] +
                   ( li_Real_s(   2179705731163145406867805569024.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[13] +
                   ( li_Real_s(   -605473814222259328665941704704.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[14] +
                   ( li_Real_s(     74139650716814899190727442432.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[15] +
                   ( li_Real_s(   3107561862519741688292298457088.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[16] +
                   ( li_Real_s(  -8389560952148789700727259791360.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[17] +
                   ( li_Real_s(  12584341431447348679022353580032.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[18] +
                   ( li_Real_s( -13982601595123492647609372246016.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[19] +
                   ( li_Real_s(  10486951200088907873487738109952.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[20] +
                   ( li_Real_s(  -5033736577654112094607275720704.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[21] +
                   ( li_Real_s(   1398260160780626364288219480064.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[22] +
                   ( li_Real_s(   -171215529910231006571632001024.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[23] +
                   ( li_Real_s(  -4102287485089335436082967216128.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[24] +
                   ( li_Real_s(  11075046106501246537855504744448.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[25] +
                   ( li_Real_s( -16612569169342549799746836365312.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[26] +
                   ( li_Real_s(  18458410200001974231842710093824.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[27] +
                   ( li_Real_s( -13843807658918667045820723888128.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[28] +
                   ( li_Real_s(   6645027680068758179986135842816.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[29] +
                   ( li_Real_s(  -1845841023042051784960112590848.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[30] +
                   ( li_Real_s(    226021349820625785429359067136.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[31] +
                   ( li_Real_s(   3354859142254694845906440683520.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[32] +
                   ( li_Real_s(  -9057195484943945600151691722752.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[33] +
                   ( li_Real_s(  13585793239171269879635394953216.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[34] +
                   ( li_Real_s( -15095325835182441527451043495936.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[35] +
                   ( li_Real_s(  11321494386569127066551340498944.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[36] +
                   ( li_Real_s(  -5434317309848194285881650053120.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[37] +
                   ( li_Real_s(   1509532586991332477770487824384.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[38] +
                   ( li_Real_s(   -184840725011845530391557439488.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[39] +
                   ( li_Real_s(  -1695752770524110705224717434880.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[40] +
                   ( li_Real_s(   4578065333829014645862807109632.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[41] +
                   ( li_Real_s(  -6867098008325447064737915338752.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[42] +
                   ( li_Real_s(   7630108906910537339658225844224.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[43] +
                   ( li_Real_s(  -5722581686530546254062311964672.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[44] +
                   ( li_Real_s(   2746839212197199939354549551104.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[45] +
                   ( li_Real_s(   -763010892850810273251765256192.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[46] +
                   ( li_Real_s(     93429905294161492791825268736.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[47] +
                   ( li_Real_s(    487476192927494438667455299584.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[48] +
                   ( li_Real_s(  -1316051430935038780926129602560.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[49] +
                   ( li_Real_s(   1974077148945446880352139214848.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[50] +
                   ( li_Real_s(  -2193419057295057934631842086912.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[51] +
                   ( li_Real_s(   1645064295061472021881731153920.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[52] +
                   ( li_Real_s(   -789630862502032949000074690560.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[53] +
                   ( li_Real_s(    219341906438310042177707704320.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[54] +
                   ( li_Real_s(    -26858192640594580538103169024.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[55] +
                   ( li_Real_s(    -61165211878904086721818787840.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[56] +
                   ( li_Real_s(    165129222289676387226537164800.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[57] +
                   ( li_Real_s(   -247693833785006676482147221504.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[58] +
                   ( li_Real_s(    275215371271637827866662535168.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[59] +
                   ( li_Real_s(   -206411528739161703819855790080.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[60] +
                   ( li_Real_s(     99077533913446719790522564608.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[61] +
                   ( li_Real_s(    -27521537223596088581337120768.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[62] +
                   ( li_Real_s(      3369984151913400304308060160.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[63];
        liVC[12] = ( li_Real_s(    -73820083259599117909997125632.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 0] +
                   ( li_Real_s(    199293888662100215808917504000.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 1] +
                   ( li_Real_s(   -298940832941182056160124993536.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 2] +
                   ( li_Real_s(    332156481014200148064011812864.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 3] +
                   ( li_Real_s(   -249117360750084296886290743296.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 4] +
                   ( li_Real_s(    119576333155275515473235542016.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 5] +
                   ( li_Real_s(    -33215648095870266808792514560.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 6] +
                   ( li_Real_s(      4067222215158259179377917952.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 7] +
                   ( li_Real_s(    438965852308631477414420021248.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 8] +
                   ( li_Real_s(  -1185086874139115005789805215744.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 9] +
                   ( li_Real_s(   1777630311629867934291092045824.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[10] +
                   ( li_Real_s(  -1975144791286246388855050600448.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[11] +
                   ( li_Real_s(   1481358593933544415747668705280.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[12] +
                   ( li_Real_s(   -711052125284556244751627583488.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[13] +
                   ( li_Real_s(    197514479282018846601111404544.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[14] +
                   ( li_Real_s(    -24185446444145355715204087808.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[15] +
                   ( li_Real_s(  -1123119838500923666470111543296.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[16] +
                   ( li_Real_s(   3032114165602924163516707373056.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[17] +
                   ( li_Real_s(  -4548171251163386515544355110912.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[18] +
                   ( li_Real_s(   5053523615673127050440872034304.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[19] +
                   ( li_Real_s(  -3790142714162829092168180695040.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[20] +
                   ( li_Real_s(   1819268503807578121400928436224.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[21] +
                   ( li_Real_s(   -505352362379725654959738322944.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[22] +
                   ( li_Real_s(     61879881123235778501831294976.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[23] +
                   ( li_Real_s(   1606905027344424807943829979136.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[24] +
                   ( li_Real_s(  -4338200902616683129656909496320.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[25] +
                   ( li_Real_s(   6507301359878132913197981630464.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[26] +
                   ( li_Real_s(  -7230334851094648284275948912640.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[27] +
                   ( li_Real_s(   5422751143202095857217138851840.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[28] +
                   ( li_Real_s(  -2602920550778695676264066318336.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[29] +
                   ( li_Real_s(    723033486766209089897960046592.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[30] +
                   ( li_Real_s(    -88534712700828611554312192000.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[31] +
                   ( li_Real_s(  -1392035856471859200356851384320.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[32] +
                   ( li_Real_s(   3758113334139646021707201773568.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[33] +
                   ( li_Real_s(  -5637170007762629547274870456320.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[34] +
                   ( li_Real_s(   6263522238190762702743390912512.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[35] +
                   ( li_Real_s(  -4697641683864374579720032878592.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[36] +
                   ( li_Real_s(   2254868010431777908693913305088.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[37] +
                   ( li_Real_s(   -626352225591539834556296200192.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[38] +
                   ( li_Real_s(     76696190928217672255637815296.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[39] +
                   ( li_Real_s(    731609754165449443197409296384.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[40] +
                   ( li_Real_s(  -1975144792472782761080590958592.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[41] +
                   ( li_Real_s(   2962717192721052747276562202624.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[42] +
                   ( li_Real_s(  -3291907996366966611924937080832.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[43] +
                   ( li_Real_s(   2468931000419961352047046950912.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[44] +
                   ( li_Real_s(  -1185086881507743008719290499072.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[45] +
                   ( li_Real_s(    329190800701910788236281643008.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[46] +
                   ( li_Real_s(    -40309077660881922644202487808.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[47] +
                   ( li_Real_s(   -216187386827526815947818008576.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[48] +
                   ( li_Real_s(    583646389207152573420700434432.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[49] +
                   ( li_Real_s(   -875469585117240000529834180608.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[50] +
                   ( li_Real_s(    972743984907309222248168030208.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[51] +
                   ( li_Real_s(   -729557989694934163853095731200.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[52] +
                   ( li_Real_s(    350187835473322531637623259136.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[53] +
                   ( li_Real_s(    -97274398833289983418540490752.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[54] +
                   ( li_Real_s(     11911150885206535287726931968.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[55] +
                   ( li_Real_s(     27682531240927414602849845248.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[56] +
                   ( li_Real_s(    -74735208380262937976622809088.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[57] +
                   ( li_Real_s(    112102812747425098497427243008.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[58] +
                   ( li_Real_s(   -124558681025722064275960233984.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[59] +
                   ( li_Real_s(     93419010906100503506487083008.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[60] +
                   ( li_Real_s(    -44841125291329489606828621824.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[61] +
                   ( li_Real_s(     12455868148605050289563631616.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[62] +
                   ( li_Real_s(     -1525208345744807314572967936.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[63];
        liVC[13] = ( li_Real_s(     12127585108749203159711219712.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 0] +
                   ( li_Real_s(    -32741138862850062093331202048.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 1] +
                   ( li_Real_s(     49111708299508218732396675072.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 2] +
                   ( li_Real_s(    -54568564785150412190319116288.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 3] +
                   ( li_Real_s(     40926423595417574100005027840.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 4] +
                   ( li_Real_s(    -19644683328145912452960223232.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 5] +
                   ( li_Real_s(      5456856480177610772271071232.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 6] +
                   ( li_Real_s(      -668186507706939933011738624.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 7] +
                   ( li_Real_s(    -77774730603767775575102455808.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 8] +
                   ( li_Real_s(    209970347162919096054146138112.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 9] +
                   ( li_Real_s(   -314955520938923610264184029184.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[10] +
                   ( li_Real_s(    349950579041067248158095966208.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[11] +
                   ( li_Real_s(   -262462934438593372922100842496.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[12] +
                   ( li_Real_s(    125982208594784485173364785152.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[13] +
                   ( li_Real_s(    -34995057955718217558424289280.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[14] +
                   ( li_Real_s(      4285109138232080963507060736.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[15] +
                   ( li_Real_s(    213550955249932650738551357440.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[16] +
                   ( li_Real_s(   -576528750069208842044310552576.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[17] +
                   ( li_Real_s(    864793125979005448846489681920.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[18] +
                   ( li_Real_s(   -960881252046781087303866515456.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[19] +
                   ( li_Real_s(    720660939709109242777701449728.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[20] +
                   ( li_Real_s(   -345917251338244606725550243840.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[21] +
                   ( li_Real_s(     96088125430776356470746251264.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[22] +
                   ( li_Real_s(    -11765892914589035216412606464.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[23] +
                   ( li_Real_s(   -325599296003621111667745619968.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[24] +
                   ( li_Real_s(    879028403138056639744216924160.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[25] +
                   ( li_Real_s(  -1318542606413382749999113175040.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[26] +
                   ( li_Real_s(   1465047342306067266739644661760.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[27] +
                   ( li_Real_s(  -1098785508016401618861440368640.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[28] +
                   ( li_Real_s(    527417044379580922089762193408.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[29] +
                   ( li_Real_s(   -146504734665158738059594825728.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[30] +
                   ( li_Real_s(     17939355274859183306084188160.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[31] +
                   ( li_Real_s(    297916764787454285506039250944.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[32] +
                   ( li_Real_s(   -804293194936411802217572466688.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[33] +
                   ( li_Real_s(   1206439794201759712855162093568.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[34] +
                   ( li_Real_s(  -1340488662155937909543381499904.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[35] +
                   ( li_Real_s(   1005366497955681353965691207680.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[36] +
                   ( li_Real_s(   -482575919571274138545580670976.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[37] +
                   ( li_Real_s(    134048866668063683079936409600.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[38] +
                   ( li_Real_s(    -16414146949335369818247790592.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[39] +
                   ( li_Real_s(   -163722399064214939921979277312.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[40] +
                   ( li_Real_s(    442005375330437418454920200192.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[41] +
                   ( li_Real_s(   -663008064070745790210312765440.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[42] +
                   ( li_Real_s(    736675627895915673966587412480.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[43] +
                   ( li_Real_s(   -552506721716093175069268770816.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[44] +
                   ( li_Real_s(    265203226750687913307818426368.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[45] +
                   ( li_Real_s(    -73667563057584710759525384192.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[46] +
                   ( li_Real_s(      9020517931598014852039180288.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[47] +
                   ( li_Real_s(     50092199393170098953383837696.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[48] +
                   ( li_Real_s(   -135235139001224758436044996608.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[49] +
                   ( li_Real_s(    202852708847462099940523638784.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[50] +
                   ( li_Real_s(   -225391899088419467984633856000.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[51] +
                   ( li_Real_s(    169043924570251895565109428224.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[52] +
                   ( li_Real_s(    -81141083897961689169019273216.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[53] +
                   ( li_Real_s(     22539189994312936182421389312.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[54] +
                   ( li_Real_s(     -2759900817591107355158773760.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[55] +
                   ( li_Real_s(     -6591078867605692652520996864.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[56] +
                   ( li_Real_s(     17794097237665374563630841856.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[57] +
                   ( li_Real_s(    -26691145903029963479949770752.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[58] +
                   ( li_Real_s(     29656828830779274160584523776.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[59] +
                   ( li_Real_s(    -22242621657172625611493998592.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[60] +
                   ( li_Real_s(     10676458409392938084259069952.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[61] +
                   ( li_Real_s(     -2965682894515731154465718272.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[62] +
                   ( li_Real_s(       363144844486252779435720704.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[63];
        liVC[14] = ( li_Real_s(     -1054572618507396113156276224.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 0] +
                   ( li_Real_s(      2847055555532784644795662336.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 1] +
                   ( li_Real_s(     -4270583336540259344313221120.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 2] +
                   ( li_Real_s(      4745092599457365544736391168.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 3] +
                   ( li_Real_s(     -3558819451804580609710358528.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 4] +
                   ( li_Real_s(      1708233337709965356176506880.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 5] +
                   ( li_Real_s(      -474509260624024741636734976.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 6] +
                   ( li_Real_s(        58103174776169435183972352.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 7] +
                   ( li_Real_s(      7118365176301614919959183360.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 8] +
                   ( li_Real_s(    -19217625009923101205806972928.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 9] +
                   ( li_Real_s(     28826437552184999940336910336.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[10] +
                   ( li_Real_s(    -32029375096627716960215367680.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[11] +
                   ( li_Real_s(     24022031348657827571600195584.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[12] +
                   ( li_Real_s(    -11530575057887721479269777408.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[13] +
                   ( li_Real_s(      3202937518271082425856557056.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[14] +
                   ( li_Real_s(      -392196430976987205325553664.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[15] +
                   ( li_Real_s(    -20564166067626686872975048704.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[16] +
                   ( li_Real_s(     55517583381940988464643178496.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[17] +
                   ( li_Real_s(    -83276375210617907765584068608.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[18] +
                   ( li_Real_s(     92529305932547649455798616064.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[19] +
                   ( li_Real_s(    -69396979546405650671922577408.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[20] +
                   ( li_Real_s(     33310550221785372571505524736.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[21] +
                   ( li_Real_s(     -9252930625699253673747546112.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[22] +
                   ( li_Real_s(      1133011914075482032651108352.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[23] +
                   ( li_Real_s(     32955394341736771835953938432.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[24] +
                   ( li_Real_s(    -88970486207816099050530275328.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[25] +
                   ( li_Real_s(    133455729560488698340580524032.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[26] +
                   ( li_Real_s(   -148284144214254765297127915520.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[27] +
                   ( li_Real_s(    111213108335672601286606323712.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[28] +
                   ( li_Real_s(    -53382292072659223830281060352.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[29] +
                   ( li_Real_s(     14828414480280495581120430080.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[30] +
                   ( li_Real_s(     -1815724223448518998496378880.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[31] +
                   ( li_Real_s(    -31637178569301741666580824064.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[32] +
                   ( li_Real_s(     85411666768622792566596698112.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[33] +
                   ( li_Real_s(   -128117500405356532325314199552.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[34] +
                   ( li_Real_s(    142352778489761019244903923712.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[35] +
                   ( li_Real_s(   -106764584044304555198176559104.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[36] +
                   ( li_Real_s(     51247000413613706444095356928.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[37] +
                   ( li_Real_s(    -14235277908552584002258599936.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[38] +
                   ( li_Real_s(      1743095255517868548455137280.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[39] +
                   ( li_Real_s(     18191377677575181943170924544.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[40] +
                   ( li_Real_s(    -49111708393798113805815775232.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[41] +
                   ( li_Real_s(     73667562738676913457793597440.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[42] +
                   ( li_Real_s(    -81852847640536441899370676224.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[43] +
                   ( li_Real_s(     61389635833777869310260150272.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[44] +
                   ( li_Real_s(    -29467025242394805445708480512.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[45] +
                   ( li_Real_s(      8185284798803868175178924032.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[46] +
                   ( li_Real_s(     -1002279772104432427967971328.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[47] +
                   ( li_Real_s(     -5800149404410790229777055744.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[48] +
                   ( li_Real_s(     15658805574688709482983194624.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[49] +
                   ( li_Real_s(    -23488208409080783047451738112.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[50] +
                   ( li_Real_s(     26098009392051791170921037824.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[51] +
                   ( li_Real_s(    -19573507076807287154612895744.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[52] +
                   ( li_Real_s(      9395283410205527023776956416.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[53] +
                   ( li_Real_s(     -2609800950194778705210900480.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[54] +
                   ( li_Real_s(       319567463547597646756577280.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[55] +
                   ( li_Real_s(       790929464223416248252235776.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[56] +
                   ( li_Real_s(     -2135291669187724077460094976.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[57] +
                   ( li_Real_s(      3202937510083403613122592768.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[58] +
                   ( li_Real_s(     -3558819462158441914942095360.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[59] +
                   ( li_Real_s(      2669114600999044693341765632.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[60] +
                   ( li_Real_s(     -1281175010257637176558747648.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[61] +
                   ( li_Real_s(       355881947680724014216511488.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[62] +
                   ( li_Real_s(       -43577381382765969540120576.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[63];
        liVC[15] = ( li_Real_s(        37663307816117768892186624.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 0] +
                   ( li_Real_s(      -101680555631429892251320320.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 1] +
                   ( li_Real_s(       152520833656389821062447104.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 2] +
                   ( li_Real_s(      -169467593155923173529616384.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 3] +
                   ( li_Real_s(       127100694999776209554898944.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 4] +
                   ( li_Real_s(       -61008333650906678617440256.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 5] +
                   ( li_Real_s(        16946759357260033198915584.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 6] +
                   ( li_Real_s(        -2075113391285457330896896.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 7] +
                   ( li_Real_s(      -263643154758512796936175616.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 8] +
                   ( li_Real_s(       711763889768063602901647360.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 9] +
                   ( li_Real_s(     -1067645836673404251909652480.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[10] +
                   ( li_Real_s(      1186273153892396462105427968.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[11] +
                   ( li_Real_s(      -889704866769349500655894528.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[12] +
                   ( li_Real_s(       427058336589548944950820864.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[13] +
                   ( li_Real_s(      -118627315833592973489078272.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[14] +
                   ( li_Real_s(        14525793784851292569468928.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[15] +
                   ( li_Real_s(       790929464353181847512940544.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[16] +
                   ( li_Real_s(     -2135291669898061090683617280.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[17] +
                   ( li_Real_s(      3202937511855233066178969600.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[18] +
                   ( li_Real_s(     -3558819464727038516380303360.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[19] +
                   ( li_Real_s(      2669114603294588027382267904.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[20] +
                   ( li_Real_s(     -1281175011505575727258927104.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[21] +
                   ( li_Real_s(       355881948059153926264455168.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[22] +
                   ( li_Real_s(       -43577381431483328312115200.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[23] +
                   ( li_Real_s(     -1318215773965356291435003904.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[24] +
                   ( li_Real_s(      3558819450193106131472089088.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[25] +
                   ( li_Real_s(     -5338229187581368789586935808.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[26] +
                   ( li_Real_s(      5931365776483579426542452736.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[27] +
                   ( li_Real_s(     -4448524340726543078561677312.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[28] +
                   ( li_Real_s(      2135291686950392423419740160.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[29] +
                   ( li_Real_s(      -593136580455959743436947456.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[30] +
                   ( li_Real_s(        72628969102148993873346560.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[31] +
                   ( li_Real_s(      1318215773950906234744864768.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[32] +
                   ( li_Real_s(     -3558819450139153095897120768.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[33] +
                   ( li_Real_s(      5338229187481042751598886912.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[34] +
                   ( li_Real_s(     -5931365776355323594185637888.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[35] +
                   ( li_Real_s(      4448524340613684257284423680.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[36] +
                   ( li_Real_s(     -2135291686889793664688586752.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[37] +
                   ( li_Real_s(       593136580439266064550854656.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[38] +
                   ( li_Real_s(       -72628969100631298459828224.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[39] +
                   ( li_Real_s(      -790929464340353707912724480.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[40] +
                   ( li_Real_s(      2135291669897699901113892864.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[41] +
                   ( li_Real_s(     -3202937511970741160723349504.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[42] +
                   ( li_Real_s(      3558819464989457307314159616.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[43] +
                   ( li_Real_s(     -2669114603577240031290458112.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[44] +
                   ( li_Real_s(      1281175011680491809441579008.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[45] +
                   ( li_Real_s(      -355881948120673663422824448.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[46] +
                   ( li_Real_s(        43577381441359794587828224.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[47] +
                   ( li_Real_s(       263643154765667559616282624.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[48] +
                   ( li_Real_s(      -711763889873167431229243392.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[49] +
                   ( li_Real_s(      1067645837060546831535046656.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[50] +
                   ( li_Real_s(     -1186273154576650310739034112.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[51] +
                   ( li_Real_s(       889704867456667550757158912.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[52] +
                   ( li_Real_s(      -427058336996665940001161216.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[53] +
                   ( li_Real_s(       118627315967684395090837504.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[54] +
                   ( li_Real_s(       -14525793804083275652661248.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[55] +
                   ( li_Real_s(       -37663307821257169708253184.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[56] +
                   ( li_Real_s(       101680555680449384792719360.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[57] +
                   ( li_Real_s(      -152520833820996229388042240.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[58] +
                   ( li_Real_s(       169467593439485504346128384.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[59] +
                   ( li_Real_s(      -127100695282614529144389632.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[60] +
                   ( li_Real_s(        61008333817676358890815488.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[61] +
                   ( li_Real_s(       -16946759411687308325289984.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[62] +
                   ( li_Real_s(         2075113398942678034415616.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[63];
        liVC[16] = ( li_Real_s(    190752722089194882113009090560.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 0] +
                   ( li_Real_s(   -816291499527207155927575691264.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 1] +
                   ( li_Real_s(   1608789749307018686953678700544.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 2] +
                   ( li_Real_s(  -1929896943908593160442297188352.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 3] +
                   ( li_Real_s(   1500804999789942881765375868928.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 4] +
                   ( li_Real_s(   -735760499985720643817746464768.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 5] +
                   ( li_Real_s(    207224972239847804626913984512.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 6] +
                   ( li_Real_s(    -25623500004483528367823388672.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 7] +
                   ( li_Real_s(            -268694974149096865792.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 8] +
                   ( li_Real_s(            1763515735924898267136.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 9] +
                   ( li_Real_s(           -4993066181563533754368.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[10] +
                   ( li_Real_s(            7862913006097513054208.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[11] +
                   ( li_Real_s(           -7420687918999439147008.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[12] +
                   ( li_Real_s(            4196394144132778426368.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[13] +
                   ( li_Real_s(           -1317736557096754479104.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[14] +
                   ( li_Real_s(             177362745653631057920.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[15] +
                   ( li_Real_s(             723657621685996748800.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[16] +
                   ( li_Real_s(           -4765012635349578416128.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[17] +
                   ( li_Real_s(           13512646643271310770176.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[18] +
                   ( li_Real_s(          -21287862886409302966272.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[19] +
                   ( li_Real_s(           20083645921196207243264.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[20] +
                   ( li_Real_s(          -11348840333606047973376.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[21] +
                   ( li_Real_s(            3560593560591255207936.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[22] +
                   ( li_Real_s(            -478827891379840417792.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[23] +
                   ( li_Real_s(           -1075952052146558205952.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[24] +
                   ( li_Real_s(            7110028457644614746112.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[25] +
                   ( li_Real_s(          -20201713552945890459648.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[26] +
                   ( li_Real_s(           31848664342848344162304.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[27] +
                   ( li_Real_s(          -30044082047415037722624.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[28] +
                   ( li_Real_s(           16967714860624601153536.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[29] +
                   ( li_Real_s(           -5319449567568617013248.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[30] +
                   ( li_Real_s(             714789558958539407360.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[31] +
                   ( li_Real_s(             954143526772098203648.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[32] +
                   ( li_Real_s(           -6329799933609254060032.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[33] +
                   ( li_Real_s(           18026764105628411494400.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[34] +
                   ( li_Real_s(          -28450594094702655438848.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[35] +
                   ( li_Real_s(           26844208529366442835968.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[36] +
                   ( li_Real_s(          -15155750388581760237568.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[37] +
                   ( li_Real_s(            4748703168531709034496.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[38] +
                   ( li_Real_s(            -637674913404988030976.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[39] +
                   ( li_Real_s(            -505758055236677992448.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[40] +
                   ( li_Real_s(            3369277423188982628352.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[41] +
                   ( li_Real_s(           -9621011580791944118272.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[42] +
                   ( li_Real_s(           15205696636631853826048.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[43] +
                   ( li_Real_s(          -14354269199822380597248.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[44] +
                   ( li_Real_s(            8103499793483568250880.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[45] +
                   ( li_Real_s(           -2538081988004405575680.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[46] +
                   ( li_Real_s(             340646970551006593024.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[47] +
                   ( li_Real_s(             148848934660970610688.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[48] +
                   ( li_Real_s(            -995863969578625138688.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[49] +
                   ( li_Real_s(            2851795863573347434496.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[50] +
                   ( li_Real_s(           -4514446388578514632704.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[51] +
                   ( li_Real_s(            4264609087285844508672.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[52] +
                   ( li_Real_s(           -2407738612224411303936.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[53] +
                   ( li_Real_s(             753943770341162876928.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[54] +
                   ( li_Real_s(            -101148685479777091584.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[55] +
                   ( li_Real_s(             -18837675563732729856.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[56] +
                   ( li_Real_s(             126552899406360297472.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[57] +
                   ( li_Real_s(            -363421738886294274048.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[58] +
                   ( li_Real_s(             576253370403966353408.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[59] +
                   ( li_Real_s(            -544775831980620906496.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[60] +
                   ( li_Real_s(             307624192389873401856.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[61] +
                   ( li_Real_s(             -96311549786040401920.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[62] +
                   ( li_Real_s(              12916334016490199040.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[63];
        liVC[17] = ( li_Real_s(   -494594557900733563349720104960.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 0] +
                   ( li_Real_s(   2116527244622900335418720387072.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 1] +
                   ( li_Real_s(  -4171361991254846304369642569728.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 2] +
                   ( li_Real_s(   5003947073601987499408970743808.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 3] +
                   ( li_Real_s(  -3891372961591638944278739156992.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 4] +
                   ( li_Real_s(   1907721866649374234428563259392.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 5] +
                   ( li_Real_s(   -537304749090193512916722909184.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 6] +
                   ( li_Real_s(     66438074963111095452435480576.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 7] +
                   ( li_Real_s(   1335269054698127542372230234112.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 8] +
                   ( li_Real_s(  -5714040497240484143395508322304.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 9] +
                   ( li_Real_s(  11261528247184756151397354831872.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[10] +
                   ( li_Real_s( -13509278611454326693592557420544.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[11] +
                   ( li_Real_s(  10505635003148775958440312832000.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[12] +
                   ( li_Real_s(  -5150323502820301650413565771776.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[13] +
                   ( li_Real_s(   1450574806644455832553940582400.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[14] +
                   ( li_Real_s(   -179364500161006163955694960640.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[15] +
                   ( li_Real_s(  -2002903582998919289887019499520.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[16] +
                   ( li_Real_s(   8571060752378429608466065653760.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[17] +
                   ( li_Real_s( -16892292390122917257718767026176.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[18] +
                   ( li_Real_s(  20263917948995490891186602770432.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[19] +
                   ( li_Real_s( -15758452535789975951980917424128.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[20] +
                   ( li_Real_s(   7725485272190225136372095647744.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[21] +
                   ( li_Real_s(  -2175862215657484310846961090560.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[22] +
                   ( li_Real_s(    269046751005154059527412252672.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[23] +
                   ( li_Real_s(   2225448426708223309344621461504.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[24] +
                   ( li_Real_s(  -9523400843928593328597828108288.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[25] +
                   ( li_Real_s(  18769213790328120812208046211072.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[26] +
                   ( li_Real_s( -22515464426189674439044883283968.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[27] +
                   ( li_Real_s(  17509391743676119468227977805824.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[28] +
                   ( li_Real_s(  -8583872546054766547222147366912.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[29] +
                   ( li_Real_s(   2417624690814642166660350345216.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[30] +
                   ( li_Real_s(   -298940835354045088481442529280.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[31] +
                   ( li_Real_s(  -1669086320831077074204899672064.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[32] +
                   ( li_Real_s(   7142550638492955855903004819456.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[33] +
                   ( li_Real_s( -14076910359155459128738795487232.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[34] +
                   ( li_Real_s(  16886598346373043780668350267392.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[35] +
                   ( li_Real_s( -13132043833583860992154336755712.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[36] +
                   ( li_Real_s(   6437904424328605161865871360000.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[37] +
                   ( li_Real_s(  -1813218522760542001495162224640.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[38] +
                   ( li_Real_s(    224205627136335418502758268928.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[39] +
                   ( li_Real_s(    801161434325420757213809475584.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[40] +
                   ( li_Real_s(  -3428424308756411738794529652736.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[41] +
                   ( li_Real_s(   6756916979151866704021554200576.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[42] +
                   ( li_Real_s(  -8105567217258409730374614646784.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[43] +
                   ( li_Real_s(   6303381050725696451919778676736.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[44] +
                   ( li_Real_s(  -3090194129732842694693386977280.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[45] +
                   ( li_Real_s(    870344892822622815492639817728.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[46] +
                   ( li_Real_s(   -107618701277938307476228145152.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[47] +
                   ( li_Real_s(   -222544842940848341114909884416.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[48] +
                   ( li_Real_s(    952340086277697883165041885184.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[49] +
                   ( li_Real_s(  -1876921384620783022550015803392.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[50] +
                   ( li_Real_s(   2251546451719219286016274726912.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[51] +
                   ( li_Real_s(  -1750939183146351361176641732608.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[52] +
                   ( li_Real_s(    858387259619921361117699375104.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[53] +
                   ( li_Real_s(   -241762470653500209413318770688.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[54] +
                   ( li_Real_s(     29894083744643401201265672192.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[55] +
                   ( li_Real_s(     27250388938193407787103420416.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[56] +
                   ( li_Real_s(   -116613071836570245028288397312.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[57] +
                   ( li_Real_s(    229827108462895475441220452352.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[58] +
                   ( li_Real_s(   -275699565748407741907384401920.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[59] +
                   ( li_Real_s(    214400716526774495156996407296.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[60] +
                   ( li_Real_s(   -105108644161889907347917111296.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[61] +
                   ( li_Real_s(     29603567874564443940300259328.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[62] +
                   ( li_Real_s(     -3660500055559332656484188160.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[63];
        liVC[18] = ( li_Real_s(    497016814539307867087822651392.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 0] +
                   ( li_Real_s(  -2126892849997856285714699780096.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 1] +
                   ( li_Real_s(   4191791064815791034019367354368.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 2] +
                   ( li_Real_s(  -5028453697561611420654490353664.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 3] +
                   ( li_Real_s(   3910430799374572202978359377920.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 4] +
                   ( li_Real_s(  -1917064855238004294290044354560.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 5] +
                   ( li_Real_s(    539936176731367342328739004416.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 6] +
                   ( li_Real_s(    -66763452663601454205282287616.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 7] +
                   ( li_Real_s(  -2126892850523421295679255871488.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 8] +
                   ( li_Real_s(   9101650214946400345484192382976.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 9] +
                   ( li_Real_s( -17938005692689251884096196444160.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[10] +
                   ( li_Real_s(  21518350908091708059078835044352.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[11] +
                   ( li_Real_s( -16733975734216581264544339329024.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[12] +
                   ( li_Real_s(   8203729568111900870313882157056.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[13] +
                   ( li_Real_s(  -2310558438508393026386619531264.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[14] +
                   ( li_Real_s(    285702024787641573529222119424.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[15] +
                   ( li_Real_s(   4191791067271393930491872673792.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[16] +
                   ( li_Real_s( -17938005699085459981471565479936.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[17] +
                   ( li_Real_s(  35353154737097412322710807117824.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[18] +
                   ( li_Real_s( -42409485343748070983398867337216.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[19] +
                   ( li_Real_s(  32980189877757109632331755290624.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[20] +
                   ( li_Real_s( -16168336993796868313329564647424.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[21] +
                   ( li_Real_s(   4553768767437782772427362664448.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[22] +
                   ( li_Real_s(   -563076412933310498023380353024.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[23] +
                   ( li_Real_s(  -5028453702288970706661029183488.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[24] +
                   ( li_Real_s(  21518350923920937511362517532672.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[25] +
                   ( li_Real_s( -42409485360165141784244338556928.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[26] +
                   ( li_Real_s(  50874227821631731660345242025984.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[27] +
                   ( li_Real_s( -39562887412524478663682038956032.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[28] +
                   ( li_Real_s(  19395464327214482827450922303488.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[29] +
                   ( li_Real_s(  -5462680530053202660290361032704.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[30] +
                   ( li_Real_s(    675463932264635341794621521920.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[31] +
                   ( li_Real_s(   3910430804268119944734403723264.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[32] +
                   ( li_Real_s( -16733975752102523601854834671616.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[33] +
                   ( li_Real_s(  32980189901735575588744586067968.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[34] +
                   ( li_Real_s( -39562887425939220269341341646848.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[35] +
                   ( li_Real_s(  30766502576020230047616487915520.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[36] +
                   ( li_Real_s( -15083090298475193980581694144512.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[37] +
                   ( li_Real_s(   4248111946698382497307802206208.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[38] +
                   ( li_Real_s(   -525281752205372689531455668224.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[39] +
                   ( li_Real_s(  -1917064858138482895053368852480.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[40] +
                   ( li_Real_s(   8203729579165860054905198215168.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[41] +
                   ( li_Real_s( -16168337010106809738038960193536.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[42] +
                   ( li_Real_s(  19395464339180436699183459598336.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[43] +
                   ( li_Real_s( -15083090302625657353970814812160.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[44] +
                   ( li_Real_s(   7394393057593854734886227673088.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[45] +
                   ( li_Real_s(  -2082610981517780497539096641536.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[46] +
                   ( li_Real_s(    257516176448586384345493667840.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[47] +
                   ( li_Real_s(    539936177667290569083853996032.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[48] +
                   ( li_Real_s(  -2310558442166072528548860526592.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[49] +
                   ( li_Real_s(   4553768773120483891988563755008.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[50] +
                   ( li_Real_s(  -5462680534717700139748109058048.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[51] +
                   ( li_Real_s(   4248111948869858922789037146112.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[52] +
                   ( li_Real_s(  -2082610982012438992110869282816.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[53] +
                   ( li_Real_s(    586561800006540657670825705472.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[54] +
                   ( li_Real_s(    -72528740767964500982860087296.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[55] +
                   ( li_Real_s(    -66763452791896015759673917440.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[56] +
                   ( li_Real_s(    285702025297674512803907502080.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[57] +
                   ( li_Real_s(   -563076413751959990481767628800.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[58] +
                   ( li_Real_s(    675463932979650181059028451328.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[59] +
                   ( li_Real_s(   -525281752581273232254305304576.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[60] +
                   ( li_Real_s(    257516176562909592383224020992.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[61] +
                   ( li_Real_s(    -72528740782990664382558502912.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[62] +
                   ( li_Real_s(      8968225067897976242353209344.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[63];
        liVC[19] = ( li_Real_s(   -256191502976647056941406748672.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 0] +
                   ( li_Real_s(   1096324832340423396437815984128.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 1] +
                   ( li_Real_s(  -2160694007698385492799152717824.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 2] +
                   ( li_Real_s(   2591958808001908609012027359232.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 3] +
                   ( li_Real_s(  -2015664489094240400875597070336.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 4] +
                   ( li_Real_s(    988167225086886728269347946496.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 5] +
                   ( li_Real_s(   -278314649612410656902923419648.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 6] +
                   ( li_Real_s(     34413783952472719914864476160.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 7] +
                   ( li_Real_s(   1352224851582400654582252306432.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 8] +
                   ( li_Real_s(  -5786599737688698011698088378368.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 9] +
                   ( li_Real_s(  11404531770068950014382244364288.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[10] +
                   ( li_Real_s( -13680824991403995399606050488320.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[11] +
                   ( li_Real_s(  10639039878839176943529002795008.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[12] +
                   ( li_Real_s(  -5215724429112576447606585032704.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[13] +
                   ( li_Real_s(   1468994802032447742824956297216.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[14] +
                   ( li_Real_s(   -181642144317706903782615416832.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[15] +
                   ( li_Real_s(  -3122781020688025985854618992640.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[16] +
                   ( li_Real_s(  13363372087911566349508062216192.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[17] +
                   ( li_Real_s( -26337228851973132135796005928960.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[18] +
                   ( li_Real_s(  31594021222124943965047486414848.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[19] +
                   ( li_Real_s( -24569428525324210951440893476864.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[20] +
                   ( li_Real_s(  12045012525048680345581857538048.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[21] +
                   ( li_Real_s(  -3392445485406296295443817037824.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[22] +
                   ( li_Real_s(    419478048306476467616533708800.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[23] +
                   ( li_Real_s(   4122378272154200421322312384512.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[24] +
                   ( li_Real_s( -17640966299614675022631321731072.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[25] +
                   ( li_Real_s(  34767734045649226840077687062528.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[26] +
                   ( li_Real_s( -41707217328107591384687150366720.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[27] +
                   ( li_Real_s(  32434063652774780659702352052224.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[28] +
                   ( li_Real_s( -15900601945628243606860904529920.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[29] +
                   ( li_Real_s(   4478361909714654784314595606528.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[30] +
                   ( li_Real_s(   -553752306942348328375431462912.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[31] +
                   ( li_Real_s(  -3371289429614974921845201960960.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[32] +
                   ( li_Real_s(  14426818524806910815526511968256.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[33] +
                   ( li_Real_s( -28433124420499210709798823657472.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[34] +
                   ( li_Real_s(  34108248130915483156622119796736.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[35] +
                   ( li_Real_s( -26524643983831684912975907389440.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[36] +
                   ( li_Real_s(  13003544986649827668231580549120.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[37] +
                   ( li_Real_s(  -3662413584495561063878858113024.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[38] +
                   ( li_Real_s(    452859776069198498013277847552.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[39] +
                   ( li_Real_s(   1704057651496590788958428856320.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[40] +
                   ( li_Real_s(  -7292204069185655288702395482112.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[41] +
                   ( li_Real_s(  14371855116676566757805599490048.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[42] +
                   ( li_Real_s( -17240412740401041003573514600448.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[43] +
                   ( li_Real_s(  13407191374739307895465172795392.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[44] +
                   ( li_Real_s(  -6572793825858447474341449826304.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[45] +
                   ( li_Real_s(   1851209760350209923786450403328.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[46] +
                   ( li_Real_s(   -228903267817522205170943918080.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[47] +
                   ( li_Real_s(   -489863588007196422470260228096.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[48] +
                   ( li_Real_s(   2096281922754768467058948571136.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[49] +
                   ( li_Real_s(  -4131461461526050752140421365760.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[50] +
                   ( li_Real_s(   4956082582891640863165566156800.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[51] +
                   ( li_Real_s(  -3854150632394346538412986597376.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[52] +
                   ( li_Real_s(   1889473848405322976989533962240.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[53] +
                   ( li_Real_s(   -532165244039254020508155379712.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[54] +
                   ( li_Real_s(     65802571915110614854891732992.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[55] +
                   ( li_Real_s(     61464766051029984706109112320.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[56] +
                   ( li_Real_s(   -263027261307976612822076358656.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[57] +
                   ( li_Real_s(    518387809257516973739850334208.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[58] +
                   ( li_Real_s(   -621855683955351438559880937472.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[59] +
                   ( li_Real_s(    483592724232431396860324741120.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[60] +
                   ( li_Real_s(   -237078384559996206040894930944.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[61] +
                   ( li_Real_s(     66772491446840031500960792576.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[62] +
                   ( li_Real_s(     -8256461164485323395765895168.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[63];
        liVC[20] = ( li_Real_s(     74181614108020686226949406720.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 0] +
                   ( li_Real_s(   -317446694017391943178768089088.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 1] +
                   ( li_Real_s(    625640457428693253784313266176.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 2] +
                   ( li_Real_s(   -750515477291196350367027691520.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 3] +
                   ( li_Real_s(    583646388051664157763740631040.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 4] +
                   ( li_Real_s(   -286129082935949807265639301120.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 5] +
                   ( li_Real_s(     80587489086162737371061157888.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 6] +
                   ( li_Real_s(     -9964694430013036758581641216.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 7] +
                   ( li_Real_s(   -441115669757394602629691080704.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 8] +
                   ( li_Real_s(   1887674092280256685185404239872.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 9] +
                   ( li_Real_s(  -3720326294690714263519078907904.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[10] +
                   ( li_Real_s(   4462886682687387413745848287232.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[11] +
                   ( li_Real_s(  -3470611562580600456348361031680.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[12] +
                   ( li_Real_s(   1701446156794338147684971446272.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[13] +
                   ( li_Real_s(   -479207748521387459232850247680.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[14] +
                   ( li_Real_s(     59254343788114667055152627712.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[15] +
                   ( li_Real_s(   1128620272523387662357921529856.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[16] +
                   ( li_Real_s(  -4829724707044394947573694070784.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[17] +
                   ( li_Real_s(   9518672689250503025204104527872.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[18] +
                   ( li_Real_s( -11418556929818870296752330637312.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[19] +
                   ( li_Real_s(   8879762928413581411991100063744.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[20] +
                   ( li_Real_s(  -4353249633004878932172303499264.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[21] +
                   ( li_Real_s(   1226081088391261838488478154752.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[22] +
                   ( li_Real_s(   -151605708710589110632392425472.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[23] +
                   ( li_Real_s(  -1614774780004212680576903151616.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[24] +
                   ( li_Real_s(   6910134296244423408298141679616.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[25] +
                   ( li_Real_s( -13618852131045550643538590433280.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[26] +
                   ( li_Real_s(  16337113743634651907130684080128.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[27] +
                   ( li_Real_s( -12704731245810464895706498859008.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[28] +
                   ( li_Real_s(   6228417029716035106642763710464.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[29] +
                   ( li_Real_s(  -1754216958742775356926755602432.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[30] +
                   ( li_Real_s(    216910046007891993592879644672.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[31] +
                   ( li_Real_s(   1398853296179189488958413209600.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[32] +
                   ( li_Real_s(  -5986137669690588342470414696448.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[33] +
                   ( li_Real_s(  11797791515873006675546622394368.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[34] +
                   ( li_Real_s( -14152577625433296304623587426304.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[35] +
                   ( li_Real_s(  11005903369350807595375411593216.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[36] +
                   ( li_Real_s(  -5395577022167592639686120570880.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[37] +
                   ( li_Real_s(   1519649803533894272910790492160.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[38] +
                   ( li_Real_s(   -187905667645417438680138645504.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[39] +
                   ( li_Real_s(   -735192783623474566264740904960.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[40] +
                   ( li_Real_s(   3146123492021788315013491982336.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[41] +
                   ( li_Real_s(  -6200543838984519172496799301632.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[42] +
                   ( li_Real_s(   7438144494720710341266818203648.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[43] +
                   ( li_Real_s(  -5784352627008769702031374942208.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[44] +
                   ( li_Real_s(   2835743607617643936317182050304.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[45] +
                   ( li_Real_s(   -798679584931657487205149966336.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[46] +
                   ( li_Real_s(     98757240188275028069596528640.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[47] +
                   ( li_Real_s(    217246155907082466356143063040.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[48] +
                   ( li_Real_s(   -929665320347601776838728220672.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[49] +
                   ( li_Real_s(   1832232774585674607563559141376.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[50] +
                   ( li_Real_s(  -2197938193915628973775218802688.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[51] +
                   ( li_Real_s(   1709250146480943255242189832192.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[52] +
                   ( li_Real_s(   -837949462905824598283555700736.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[53] +
                   ( li_Real_s(    236006219837570858330879950848.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[54] +
                   ( li_Real_s(    -29182319642215535130059997184.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[55] +
                   ( li_Real_s(    -27818105331578969654632120320.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[56] +
                   ( li_Real_s(    119042510547091834112680394752.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[57] +
                   ( li_Real_s(   -234615172399917562805897658368.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[58] +
                   ( li_Real_s(    281443305390731939944922611712.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[59] +
                   ( li_Real_s(   -218867396874414564177661132800.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[60] +
                   ( li_Real_s(    107298406874034569491968425984.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[61] +
                   ( li_Real_s(    -30220308649428749213073670144.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[62] +
                   ( li_Real_s(      3736760443482929467786002432.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[63];
        liVC[21] = ( li_Real_s(    -12186979466184796865237614592.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 0] +
                   ( li_Real_s(     52151956910335872139922505728.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 1] +
                   ( li_Real_s(   -102783789536445189983976816640.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 2] +
                   ( li_Real_s(    123298971429971736884143980544.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 3] +
                   ( li_Real_s(    -95884763903523513099775639552.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 4] +
                   ( li_Real_s(     47006920853958461374848827392.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 5] +
                   ( li_Real_s(    -13239373233709983512448204800.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 6] +
                   ( li_Real_s(      1637056945591949589244542976.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 7] +
                   ( li_Real_s(     78155629217680197595386871808.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 8] +
                   ( li_Real_s(   -334452767372362324350773231616.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 9] +
                   ( li_Real_s(    659156911841003776910641070080.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[10] +
                   ( li_Real_s(   -790721665714952268026130464768.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[11] +
                   ( li_Real_s(    614913160884530107984382001152.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[12] +
                   ( li_Real_s(   -301457427827409357828639424512.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[13] +
                   ( li_Real_s(     84904676366113242594465021952.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[14] +
                   ( li_Real_s(    -10498517394603172569192333312.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[15] +
                   ( li_Real_s(   -214596812498814336525867679744.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[16] +
                   ( li_Real_s(    918327938026220567318337945600.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[17] +
                   ( li_Real_s(  -1809888471259671434948270620672.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[18] +
                   ( li_Real_s(   2171134067537286398000788144128.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[19] +
                   ( li_Real_s(  -1688405630446133780358813974528.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[20] +
                   ( li_Real_s(    827730565828070767710928109568.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[21] +
                   ( li_Real_s(   -233128094833271874612086439936.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[22] +
                   ( li_Real_s(     28826437646313486706798493696.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[23] +
                   ( li_Real_s(    327193905554952091054427340800.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[24] +
                   ( li_Real_s(  -1400166671488253064400447995904.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[25] +
                   ( li_Real_s(   2759521312721131878556662497280.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[26] +
                   ( li_Real_s(  -3310309352461125713857840414720.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[27] +
                   ( li_Real_s(   2574297476035843516122347339776.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[28] +
                   ( li_Real_s(  -1262033641882915732336892968960.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[29] +
                   ( li_Real_s(    355448391940527421223176503296.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[30] +
                   ( li_Real_s(    -43951420420158716307665059840.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[31] +
                   ( li_Real_s(   -299375800275209869770178428928.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[32] +
                   ( li_Real_s(   1281124161310716781677791674368.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[33] +
                   ( li_Real_s(  -2524906141415846258146136817664.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[34] +
                   ( li_Real_s(   3028866048837110906918461767680.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[35] +
                   ( li_Real_s(  -2355430080846904947584652017664.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[36] +
                   ( li_Real_s(   1154735235960676077441497694208.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[37] +
                   ( li_Real_s(   -325228083586133032822678487040.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[38] +
                   ( li_Real_s(     40214660015589955257801637888.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[39] +
                   ( li_Real_s(    164524223002414038496309149696.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[40] +
                   ( li_Real_s(   -704051419757551085198916976640.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[41] +
                   ( li_Real_s(   1387581163062568643453754802176.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[42] +
                   ( li_Real_s(  -1664536121263619119036271427584.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[43] +
                   ( li_Real_s(   1294444319348366051851175460864.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[44] +
                   ( li_Real_s(   -634593435308039300225572012032.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[45] +
                   ( li_Real_s(    178731539840052475304731475968.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[46] +
                   ( li_Real_s(    -22100268924190965773396606976.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[47] +
                   ( li_Real_s(    -50337523949722867393082949632.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[48] +
                   ( li_Real_s(    215410257279076181679104065536.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[49] +
                   ( li_Real_s(   -424541740788185870223343091712.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[50] +
                   ( li_Real_s(    509278362504319211708392407040.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[51] +
                   ( li_Real_s(   -396045766096840944515912040448.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[52] +
                   ( li_Real_s(    194159022136889227620059709440.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[53] +
                   ( li_Real_s(    -54684368085659612583112474624.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[54] +
                   ( li_Real_s(      6761757000124456004592074752.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[55] +
                   ( li_Real_s(      6623358414673770871663886336.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[56] +
                   ( li_Real_s(    -28343454906880341837638270976.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[57] +
                   ( li_Real_s(     55860755371953944767131287552.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[58] +
                   ( li_Real_s(    -67010310863798678143046254592.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[59] +
                   ( li_Real_s(     52111285020027775064498765824.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[60] +
                   ( li_Real_s(    -25547239758741447565270581248.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[61] +
                   ( li_Real_s(      7195311591337494214227263488.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[62] +
                   ( li_Real_s(      -889704868572044306688245760.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[63];
        liVC[22] = ( li_Real_s(      1059737345698007624496185344.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 0] +
                   ( li_Real_s(     -4534952780039188418203222016.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 1] +
                   ( li_Real_s(      8937720843836428440276303872.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 2] +
                   ( li_Real_s(    -10721649712298820947534675968.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 3] +
                   ( li_Real_s(      8337805578125908868182573056.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 4] +
                   ( li_Real_s(     -4087558347069138371400957952.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 5] +
                   ( li_Real_s(      1151249850114557437043277824.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 6] +
                   ( li_Real_s(      -142352778368018395391066112.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 7] +
                   ( li_Real_s(     -7153227086440466015064162304.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 8] +
                   ( li_Real_s(     30610931286731038160945414144.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 9] +
                   ( li_Real_s(    -60329615760092280511770132480.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[10] +
                   ( li_Real_s(     72371135662489048010937335808.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[11] +
                   ( li_Real_s(    -56280187753012517717281865728.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[12] +
                   ( li_Real_s(     27591018900416070020644208640.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[13] +
                   ( li_Real_s(     -7770936506554154996708933632.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[14] +
                   ( li_Real_s(       960881256463293972062666752.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[15] +
                   ( li_Real_s(     20664878255624370111807225856.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[16] +
                   ( li_Real_s(    -88431579314808070799481634816.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[17] +
                   ( li_Real_s(    174285556764506100971740332032.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[18] +
                   ( li_Real_s(   -209072169891875159070772035584.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[19] +
                   ( li_Real_s(    162587209255647877427829407744.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[20] +
                   ( li_Real_s(    -79707388043473855281700536320.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[21] +
                   ( li_Real_s(     22449372164344612636411822080.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[22] +
                   ( li_Real_s(     -2775879189965901284602019840.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[23] +
                   ( li_Real_s(    -33116792081884892972839862272.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[24] +
                   ( li_Real_s(    141717274582353091329269956608.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[25] +
                   ( li_Real_s(   -279303776981499884312876548096.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[26] +
                   ( li_Real_s(    335051554497693444363897536512.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[27] +
                   ( li_Real_s(   -260556425262940113978821443584.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[28] +
                   ( li_Real_s(    127736198885499183218953289728.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[29] +
                   ( li_Real_s(    -35976557986198552276644134912.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[30] +
                   ( li_Real_s(      4448524346977635018863542272.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[31] +
                   ( li_Real_s(     31792120401314153889313849344.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[32] +
                   ( li_Real_s(   -136048583618189458800547725312.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[33] +
                   ( li_Real_s(    268131625957312548233879224320.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[34] +
                   ( li_Real_s(   -321649492403589435107909304320.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[35] +
                   ( li_Real_s(    250134168331555662388787150848.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[36] +
                   ( li_Real_s(   -122626750973546417010702811136.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[37] +
                   ( li_Real_s(     34537495679973588237629259776.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[38] +
                   ( li_Real_s(     -4270583374830723194310098944.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[39] +
                   ( li_Real_s(    -18280469231301484107041603584.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[40] +
                   ( li_Real_s(     78227935584406994354784174080.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[41] +
                   ( li_Real_s(   -154175684936375302216063385600.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[42] +
                   ( li_Real_s(    184948458147906603513718767616.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[43] +
                   ( li_Real_s(   -143827146803981232713582510080.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[44] +
                   ( li_Real_s(     70510381816367186099700760576.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[45] +
                   ( li_Real_s(    -19859060017755881057988640768.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[46] +
                   ( li_Real_s(      2455585440733178248879407104.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[47] +
                   ( li_Real_s(      5828555407033095995632123904.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[48] +
                   ( li_Real_s(    -24942240330997374476521308160.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[49] +
                   ( li_Real_s(     49157464761416490519594270720.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[50] +
                   ( li_Real_s(    -58969073610467500505843105792.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[51] +
                   ( li_Real_s(     45857930862708661679005106176.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[52] +
                   ( li_Real_s(    -22481571012293630649648021504.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[53] +
                   ( li_Real_s(      6331874207960752732017524736.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[54] +
                   ( li_Real_s(      -782940285360506976547635200.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[55] +
                   ( li_Real_s(      -794803010021975444114374656.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[56] +
                   ( li_Real_s(      3401214590411326321583980544.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[57] +
                   ( li_Real_s(     -6703290648751195275659313152.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[58] +
                   ( li_Real_s(      8041237309616565446730842112.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[59] +
                   ( li_Real_s(     -6253354207634574169151111168.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[60] +
                   ( li_Real_s(      3065668773848204132195762176.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[61] +
                   ( li_Real_s(      -863437391809340220882550784.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[62] +
                   ( li_Real_s(       106764584341223817590341632.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[63];
        liVC[23] = ( li_Real_s(       -37847762381032666121109504.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 0] +
                   ( li_Real_s(       161962599508578839266590720.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 1] +
                   ( li_Real_s(      -319204316464566908609363968.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 2] +
                   ( li_Real_s(       382916062103157240219303936.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 3] +
                   ( li_Real_s(      -297778771531681013149204480.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 4] +
                   ( li_Real_s(       145984227174829438370054144.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 5] +
                   ( li_Real_s(       -41116066228359198549213184.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 6] +
                   ( li_Real_s(         5084027819071993314017280.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 7] +
                   ( li_Real_s(       264934336762268442202996736.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 8] +
                   ( li_Real_s(     -1133738197270204032697237504.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 9] +
                   ( li_Real_s(      2234430217415607888526704640.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[10] +
                   ( li_Real_s(     -2680412438279453523935494144.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[11] +
                   ( li_Real_s(      2084451404171542720350781440.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[12] +
                   ( li_Real_s(     -1021889592211405641986605056.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[13] +
                   ( li_Real_s(       287812464231595163435139072.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[14] +
                   ( li_Real_s(       -35588194819950719543541760.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[15] +
                   ( li_Real_s(      -794803010440936378419118080.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[16] +
                   ( li_Real_s(      3401214592961675428047618048.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[17] +
                   ( li_Real_s(     -6703290655724284824875171840.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[18] +
                   ( li_Real_s(      8041237320496347352783650816.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[19] +
                   ( li_Real_s(     -6253354217946673823736659968.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[20] +
                   ( li_Real_s(      3065668779736912433145446400.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[21] +
                   ( li_Real_s(      -863437393676385594197934080.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[22] +
                   ( li_Real_s(       106764584593344479539232768.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[23] +
                   ( li_Real_s(      1324671684142234050641264640.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[24] +
                   ( li_Real_s(     -5668690988865551029407580160.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[25] +
                   ( li_Real_s(     11172151094685158523715715072.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[26] +
                   ( li_Real_s(    -13402062203715754993117036544.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[27] +
                   ( li_Real_s(     10422257032607317232394960896.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[28] +
                   ( li_Real_s(     -5109447967726760164583276544.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[29] +
                   ( li_Real_s(      1439062323258320274956746752.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[30] +
                   ( li_Real_s(      -177940974384968464445997056.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[31] +
                   ( li_Real_s(     -1324671684095825588978188288.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[32] +
                   ( li_Real_s(      5668690988600169604392681472.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[33] +
                   ( li_Real_s(    -11172151093920448186597507072.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[34] +
                   ( li_Real_s(     13402062202397020537971802112.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[35] +
                   ( li_Real_s(    -10422257031229662148140466176.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[36] +
                   ( li_Real_s(      5109447966878561710544781312.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[37] +
                   ( li_Real_s(     -1439062322975890647275274240.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[38] +
                   ( li_Real_s(       177940974346071934943363072.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[39] +
                   ( li_Real_s(       794803010385318819678650368.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[40] +
                   ( li_Real_s(     -3401214592688497366080159744.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[41] +
                   ( li_Real_s(      6703290654971993471592693760.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[42] +
                   ( li_Real_s(     -8041237319159466557733601280.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[43] +
                   ( li_Real_s(      6253354216484890706794512384.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[44] +
                   ( li_Real_s(     -3065668778803451250419433472.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[45] +
                   ( li_Real_s(       863437393358727201645658112.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[46] +
                   ( li_Real_s(      -106764584549512517217419264.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[47] +
                   ( li_Real_s(      -264934336761981194790240256.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[48] +
                   ( li_Real_s(      1133738197343171060290289664.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[49] +
                   ( li_Real_s(     -2234430217683953871767994368.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[50] +
                   ( li_Real_s(      2680412438676177110446374912.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[51] +
                   ( li_Real_s(     -2084451404477114319017869312.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[52] +
                   ( li_Real_s(      1021889592343585219026092032.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[53] +
                   ( li_Real_s(      -287812464264146411333877760.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[54] +
                   ( li_Real_s(        35588194824262085024677888.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[55] +
                   ( li_Real_s(        37847762389115906241331200.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[56] +
                   ( li_Real_s(      -161962599584050519987978240.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[57] +
                   ( li_Real_s(       319204316706291310160510976.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[58] +
                   ( li_Real_s(      -382916062496859574935486464.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[59] +
                   ( li_Real_s(       297778771902458977102856192.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[60] +
                   ( li_Real_s(      -145984227382108288106627072.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[61] +
                   ( li_Real_s(        41116066293097884846915584.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[62] +
                   ( li_Real_s(        -5084027827938054574702592.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[63];
        liVC[24] = ( li_Real_s(    -98325097168374433335839031296.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 0] +
                   ( li_Real_s(    518977555318963276345530908672.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 1] +
                   ( li_Real_s(  -1198508707914980945299035389952.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 2] +
                   ( li_Real_s(   1582149444070540406673901617152.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 3] +
                   ( li_Real_s(  -1293885069278910181729221214208.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 4] +
                   ( li_Real_s(    654009333313424398304510214144.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 5] +
                   ( li_Real_s(   -188007347232611287515810234368.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 6] +
                   ( li_Real_s(     23589888891948551051684085760.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 7] +
                   ( li_Real_s(             229805531804500230144.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 8] +
                   ( li_Real_s(           -1516369283004818522112.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 9] +
                   ( li_Real_s(            4313650869882511687680.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[10] +
                   ( li_Real_s(           -6820783024042019913728.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[11] +
                   ( li_Real_s(            6460082283868094201856.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[12] +
                   ( li_Real_s(           -3664725939478008954880.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[13] +
                   ( li_Real_s(            1154078734460710944768.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[14] +
                   ( li_Real_s(            -155739173490968100864.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[15] +
                   ( li_Real_s(            -616054686116307927040.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[16] +
                   ( li_Real_s(            4079208658446657257472.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[17] +
                   ( li_Real_s(          -11625153376486305038336.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[18] +
                   ( li_Real_s(           18392953474609227759616.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[19] +
                   ( li_Real_s(          -17417478869856513163264.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[20] +
                   ( li_Real_s(            9874976957690145669120.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[21] +
                   ( li_Real_s(           -3107478770602971496448.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[22] +
                   ( li_Real_s(             419026612316065103872.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[23] +
                   ( li_Real_s(             913157696543674204160.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[24] +
                   ( li_Real_s(           -6069433525302974218240.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[25] +
                   ( li_Real_s(           17333901158130439421952.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[26] +
                   ( li_Real_s(          -27449662192071565377536.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[27] +
                   ( li_Real_s(           25995492127681651146752.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[28] +
                   ( li_Real_s(          -14732192134918010044416.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[29] +
                   ( li_Real_s(            4633051743766012493824.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[30] +
                   ( li_Real_s(            -624314873829187256320.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[31] +
                   ( li_Real_s(            -808192615763177897984.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[32] +
                   ( li_Real_s(            5394076170149672517632.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[33] +
                   ( li_Real_s(          -15443956439276970835968.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[34] +
                   ( li_Real_s(           24487302235505347788800.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[35] +
                   ( li_Real_s(          -23198397190327716806656.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[36] +
                   ( li_Real_s(           13144643934724372299776.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[37] +
                   ( li_Real_s(           -4131962659001336332288.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[38] +
                   ( li_Real_s(             556486563989809463296.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[39] +
                   ( li_Real_s(             427840801481908813824.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[40] +
                   ( li_Real_s(           -2868226637048519852032.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[41] +
                   ( li_Real_s(            8235621198680812421120.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[42] +
                   ( li_Real_s(          -13078609424389534384128.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[43] +
                   ( li_Real_s(           12398170235750089490432.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[44] +
                   ( li_Real_s(           -7025417468636895903744.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[45] +
                   ( li_Real_s(            2207852059076097736704.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[46] +
                   ( li_Real_s(            -297230764913957994496.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[47] +
                   ( li_Real_s(            -125799477093544443904.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[48] +
                   ( li_Real_s(             847213230170766311424.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[49] +
                   ( li_Real_s(           -2440065541389508673536.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[50] +
                   ( li_Real_s(            3881873464276834844672.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[51] +
                   ( li_Real_s(           -3683012789779211223040.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[52] +
                   ( li_Real_s(            2087458851761385897984.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[53] +
                   ( li_Real_s(            -655949724755422085120.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[54] +
                   ( li_Real_s(              88281986808700010496.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[55] +
                   ( li_Real_s(              15908626333495246848.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[56] +
                   ( li_Real_s(            -107614499252153843712.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[57] +
                   ( li_Real_s(             310882846324548501504.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[58] +
                   ( li_Real_s(            -495485330503580385280.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[59] +
                   ( li_Real_s(             470534298590607704064.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[60] +
                   ( li_Real_s(            -266773726056653750272.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[61] +
                   ( li_Real_s(              83827272233297805312.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[62] +
                   ( li_Real_s(             -11279487669565440000.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[63];
        liVC[25] = ( li_Real_s(    254942930418314819871474450432.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 0] +
                   ( li_Real_s(  -1345634660669342350408530526208.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 1] +
                   ( li_Real_s(   3107561862417791451727698853888.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 2] +
                   ( li_Real_s(  -4102287484640996463678700126208.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 3] +
                   ( li_Real_s(   3354859141705139160726881959936.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 4] +
                   ( li_Real_s(  -1695752770185973689802299539456.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 5] +
                   ( li_Real_s(    487476192819674182201043320832.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 6] +
                   ( li_Real_s(    -61165211864579139061757771776.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 7] +
                   ( li_Real_s(   -688275680089758186934668099584.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 8] +
                   ( li_Real_s(   3632842886815750845008296542208.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 9] +
                   ( li_Real_s(  -8389560954899374432142858649600.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[10] +
                   ( li_Real_s(  11075046108806799064893233299456.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[11] +
                   ( li_Real_s(  -9057195486168962979393299283968.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[12] +
                   ( li_Real_s(   4578065334277996507113881337856.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[13] +
                   ( li_Real_s(  -1316051431046172983030844489728.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[14] +
                   ( li_Real_s(    165129222303722762620584853504.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[15] +
                   ( li_Real_s(   1032413520733151526761961357312.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[16] +
                   ( li_Real_s(  -5449264334509866695742321590272.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[17] +
                   ( li_Real_s(  12584341445546547356049424252928.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[18] +
                   ( li_Real_s( -16612569185531114710898969673728.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[19] +
                   ( li_Real_s(  13585793251508905828614819282944.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[20] +
                   ( li_Real_s(  -6867098014480323020681195290624.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[21] +
                   ( li_Real_s(   1974077150754101216428408438784.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[22] +
                   ( li_Real_s(   -247693834021405511550544904192.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[23] +
                   ( li_Real_s(  -1147126134926772014106282033152.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[24] +
                   ( li_Real_s(   6054738154994201725231796584448.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[25] +
                   ( li_Real_s( -13982601622943157539199978045440.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[26] +
                   ( li_Real_s(  18458410234036953386375907901440.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[27] +
                   ( li_Real_s( -15095325862399434716906929520640.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[28] +
                   ( li_Real_s(   7630108920861921121515555782656.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[29] +
                   ( li_Real_s(  -2193419061436728592698475282432.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[30] +
                   ( li_Real_s(    275215371813000057949150773248.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[31] +
                   ( li_Real_s(    860344601753400811696458563584.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[32] +
                   ( li_Real_s(  -4541053620220625152433035673600.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[33] +
                   ( li_Real_s(  10486951229190515643609914540032.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[34] +
                   ( li_Real_s( -13843807695310093906780564226048.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[35] +
                   ( li_Real_s(  11321494416093487733694785388544.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[36] +
                   ( li_Real_s(  -5722581701765713760798900224000.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[37] +
                   ( li_Real_s(   1645064299588776627365868470272.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[38] +
                   ( li_Real_s(   -206411529329748664857596526592.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[39] +
                   ( li_Real_s(   -412965409075023145235212402688.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[40] +
                   ( li_Real_s(   2179705739374905103148761743360.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[41] +
                   ( li_Real_s(  -5033736595037627227988784316416.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[42] +
                   ( li_Real_s(   6645027702018472975558590332928.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[43] +
                   ( li_Real_s(  -5434317327756158099470080278528.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[44] +
                   ( li_Real_s(   2746839221454853376572869574656.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[45] +
                   ( li_Real_s(   -789630865250643555666513362944.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[46] +
                   ( li_Real_s(     99077534271222772103624261632.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[47] +
                   ( li_Real_s(    114712613684943500993380745216.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[48] +
                   ( li_Real_s(   -605473816874836724990703828992.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[49] +
                   ( li_Real_s(   1398260166439894129088305037312.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[50] +
                   ( li_Real_s(  -1845841030230998688393978707968.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[51] +
                   ( li_Real_s(   1509532592876342610942566072320.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[52] +
                   ( li_Real_s(   -763010895896168829602668478464.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[53] +
                   ( li_Real_s(    219341907341848059934261903360.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[54] +
                   ( li_Real_s(    -27521537341022883692744278016.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[55] +
                   ( li_Real_s(    -14046442496961397856290209792.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[56] +
                   ( li_Real_s(     74139651081856022962870681600.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[57] +
                   ( li_Real_s(   -171215530693420598123359633408.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[58] +
                   ( li_Real_s(    226021350819704573055834521600.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[59] +
                   ( li_Real_s(   -184840725831595238165162491904.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[60] +
                   ( li_Real_s(     93429905718637491659586142208.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[61] +
                   ( li_Real_s(    -26858192766468971864224956416.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[62] +
                   ( li_Real_s(      3369984168255116722256740352.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[63];
        liVC[26] = ( li_Real_s(   -256191502933633704665972473856.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 0] +
                   ( li_Real_s(   1352224850915250916582469140480.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 1] +
                   ( li_Real_s(  -3122781018122856702897677139968.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 2] +
                   ( li_Real_s(   4122378267564716023157954183168.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 3] +
                   ( li_Real_s(  -3371289425052064013282143371264.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 4] +
                   ( li_Real_s(   1704057648866075119833271238656.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 5] +
                   ( li_Real_s(   -489863587176678678356356497408.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 6] +
                   ( li_Real_s(     61464765939161141708272435200.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 7] +
                   ( li_Real_s(   1096324832486895937443623600128.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 8] +
                   ( li_Real_s(  -5786599736092728138349227802624.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 9] +
                   ( li_Real_s(  13363372078834000602389219901440.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[10] +
                   ( li_Real_s( -17640966281513627256318729388032.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[11] +
                   ( li_Real_s(  14426818506031041429248910819328.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[12] +
                   ( li_Real_s(  -7292204058145758593947543797760.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[13] +
                   ( li_Real_s(   2096281919230067595519006343168.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[14] +
                   ( li_Real_s(   -263027260829897768434747310080.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[15] +
                   ( li_Real_s(  -2160694008916529253109486059520.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[16] +
                   ( li_Real_s(  11404531770782612929333510012928.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[17] +
                   ( li_Real_s( -26337228840890133740807404912640.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[18] +
                   ( li_Real_s(  34767734017069189950000542515200.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[19] +
                   ( li_Real_s( -28433124388423903127321672941568.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[20] +
                   ( li_Real_s(  14371855097177664717551988375552.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[21] +
                   ( li_Real_s(  -4131461455187178544571059535872.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[22] +
                   ( li_Real_s(    518387808388284316904232845312.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[23] +
                   ( li_Real_s(   2591958810660445956493660913664.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[24] +
                   ( li_Real_s( -13680824997373372590497567080448.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[25] +
                   ( li_Real_s(  31594021218225398644897312931840.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[26] +
                   ( li_Real_s( -41707217304104999645070495842304.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[27] +
                   ( li_Real_s(  34108248099927258955799286775808.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[28] +
                   ( li_Real_s( -17240412720576249487084119654400.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[29] +
                   ( li_Real_s(   4956082576275519744185882116096.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[30] +
                   ( li_Real_s(   -621855683034000452824053317632.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[31] +
                   ( li_Real_s(  -2015664492003985439347213074432.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[32] +
                   ( li_Real_s(  10639039887110956393518902280192.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[33] +
                   ( li_Real_s( -24569428529016739307519727370240.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[34] +
                   ( li_Real_s(  32434063641503657901079230676992.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[35] +
                   ( li_Real_s( -26524643965124267989234524094464.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[36] +
                   ( li_Real_s(  13407191361882476715244154519552.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[37] +
                   ( li_Real_s(  -3854150627953907644016548118528.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[38] +
                   ( li_Real_s(    483592723601808174007074160640.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[39] +
                   ( li_Real_s(    988167226873816825643088740352.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[40] +
                   ( li_Real_s(  -5215724434731919238760077721600.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[41] +
                   ( li_Real_s(  12045012529773803031423453495296.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[42] +
                   ( li_Real_s( -15900601943315892896185660211200.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[43] +
                   ( li_Real_s(  13003544979820675027878203621376.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[44] +
                   ( li_Real_s(  -6572793820665104675540559724544.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[45] +
                   ( li_Real_s(   1889473846532235922519451762688.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[46] +
                   ( li_Real_s(   -237078384287617128387015868416.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[47] +
                   ( li_Real_s(   -278314650205668674732159926272.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[48] +
                   ( li_Real_s(   1468994804014722318460822487040.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[49] +
                   ( li_Real_s(  -3392445487505590151997464510464.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[50] +
                   ( li_Real_s(   4478361909941789890871352623104.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[51] +
                   ( li_Real_s(  -3662413583235097540820077641728.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[52] +
                   ( li_Real_s(   1851209759211044101291453186048.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[53] +
                   ( li_Real_s(   -532165243602560090102873194496.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[54] +
                   ( li_Real_s(     66772491381357675326807736320.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[55] +
                   ( li_Real_s(     34413784035886998032276783104.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[56] +
                   ( li_Real_s(   -181642144608592363020894601216.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[57] +
                   ( li_Real_s(    419478048656910139609021677568.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[58] +
                   ( li_Real_s(   -553752307077781561532135505920.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[59] +
                   ( li_Real_s(    452859775996683718244427628544.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[60] +
                   ( li_Real_s(   -228903267718243764269653950464.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[61] +
                   ( li_Real_s(     65802571873003453674791370752.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[62] +
                   ( li_Real_s(     -8256461157860205087485329408.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[63];
        liVC[27] = ( li_Real_s(    132056067837569362793152380928.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 0] +
                   ( li_Real_s(   -697015687840474009093015601152.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 1] +
                   ( li_Real_s(   1609663775803573116290730033152.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 2] +
                   ( li_Real_s(  -2124914596597255786685597220864.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 3] +
                   ( li_Real_s(   1737759527073503693584472211456.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 4] +
                   ( li_Real_s(   -878370866650711643677580591104.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 5] +
                   ( li_Real_s(    252504311631446102669218807808.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 6] +
                   ( li_Real_s(    -31682531257673032822121562112.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 7] +
                   ( li_Real_s(   -697015688154380673357761740800.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 8] +
                   ( li_Real_s(   3678974221554829647763690487808.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 9] +
                   ( li_Real_s(  -8496095053148404044864604340224.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[10] +
                   ( li_Real_s(  11215681601836590349168314155008.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[11] +
                   ( li_Real_s(  -9172207480949311499021817217024.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[12] +
                   ( li_Real_s(   4636199491209437114287144304640.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[13] +
                   ( li_Real_s(  -1332763193421798407322956988416.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[14] +
                   ( li_Real_s(    167226101073035824498131075072.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[15] +
                   ( li_Real_s(   1609663777255839880929639137280.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[16] +
                   ( li_Real_s(  -8496095056882222528227077783552.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[17] +
                   ( li_Real_s(  19620586296203635252642732572672.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[18] +
                   ( li_Real_s( -25901104848937522934570727505920.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[19] +
                   ( li_Real_s(  21181976819122991501231475654656.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[20] +
                   ( li_Real_s( -10706677794875021300517916639232.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[21] +
                   ( li_Real_s(   3077836947610506726298791968768.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[22] +
                   ( li_Real_s(   -386186139498193227725523648512.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[23] +
                   ( li_Real_s(  -2124914599365040609503054135296.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[24] +
                   ( li_Real_s(  11215681610951833210769738039296.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[25] +
                   ( li_Real_s( -25901104858173460014385866997760.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[26] +
                   ( li_Real_s(  34192007446754718819853774356480.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[27] +
                   ( li_Real_s( -27962294021048836587172694851584.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[28] +
                   ( li_Real_s(  14133868386703741911017468198912.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[29] +
                   ( li_Real_s(  -4063047676559595399766928785408.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[30] +
                   ( li_Real_s(    509803710736597010891010998272.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[31] +
                   ( li_Real_s(   1737759529914864104989257629696.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[32] +
                   ( li_Real_s(  -9172207491134206559919821291520.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[33] +
                   ( li_Real_s(  21181976832404268931933653696512.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[34] +
                   ( li_Real_s( -27962294028262594383903698452480.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[35] +
                   ( li_Real_s(  22867621576560491874180992598016.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[36] +
                   ( li_Real_s( -11558706645343975447788154519552.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[37] +
                   ( li_Real_s(   3322768749426731744648656584704.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[38] +
                   ( li_Real_s(   -416918523565574705010096209920.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[39] +
                   ( li_Real_s(   -878370868325869998124356861952.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[40] +
                   ( li_Real_s(   4636199497462916006371980738560.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[41] +
                   ( li_Real_s( -10706677803838155084704902021120.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[42] +
                   ( li_Real_s(  14133868393095369847571801440256.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[43] +
                   ( li_Real_s( -11558706647534679428928494370816.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[44] +
                   ( li_Real_s(   5842483395328012304935072825344.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[45] +
                   ( li_Real_s(  -1679532307732304068545739751424.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[46] +
                   ( li_Real_s(    210736341544710421424638001152.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[47] +
                   ( li_Real_s(    252504312170864255456310722560.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[48] +
                   ( li_Real_s(  -1332763195488529549720855511040.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[49] +
                   ( li_Real_s(   3077836950737461782173370548224.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[50] +
                   ( li_Real_s(  -4063047679072312383763793313792.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[51] +
                   ( li_Real_s(   3322768750599365504824504221696.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[52] +
                   ( li_Real_s(  -1679532308008916283558742458368.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[53] +
                   ( li_Real_s(    482813314554253460724298809344.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[54] +
                   ( li_Real_s(    -60580145492187243531930173440.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[55] +
                   ( li_Real_s(    -31682531331716639528929198080.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[56] +
                   ( li_Real_s(    167226101362369371452316057600.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[57] +
                   ( li_Real_s(   -386186139952807121785601392640.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[58] +
                   ( li_Real_s(    509803711129319835228228812800.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[59] +
                   ( li_Real_s(   -416918523775666290620790472704.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[60] +
                   ( li_Real_s(    210736341611797800692553351168.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[61] +
                   ( li_Real_s(    -60580145501580283407090319360.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[62] +
                   ( li_Real_s(      7601186458290951982940160000.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[63];
        liVC[28] = ( li_Real_s(    -38237537748508790185722380288.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 0] +
                   ( li_Real_s(    201824604605459839830779232256.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 1] +
                   ( li_Real_s(   -466086719136835658663132659712.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 2] +
                   ( li_Real_s(    615280338528844996664946065408.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 3] +
                   ( li_Real_s(   -503177526261249604870918373376.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 4] +
                   ( li_Real_s(    254336962614217183492892000256.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 5] +
                   ( li_Real_s(    -73113968269001471993034309632.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 6] +
                   ( li_Real_s(      9173845667061540838656966656.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 7] +
                   ( li_Real_s(    227376787088450298307940450304.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 8] +
                   ( li_Real_s(  -1200135596094408607721655894016.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 9] +
                   ( li_Real_s(   2771551385979839307434973724672.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[10] +
                   ( li_Real_s(  -3658720588613510207157858992128.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[11] +
                   ( li_Real_s(   2992109222668379015518412079104.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[12] +
                   ( li_Real_s(  -1512396583557172357447775420416.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[13] +
                   ( li_Real_s(    434766990610333774824192606208.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[14] +
                   ( li_Real_s(    -54551618081911777912088952832.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[15] +
                   ( li_Real_s(   -581756824900225500527485517824.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[16] +
                   ( li_Real_s(   3070617202779000327726396604416.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[17] +
                   ( li_Real_s(  -7091176524911684876166773080064.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[18] +
                   ( li_Real_s(   9361050884855456135896337743872.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[19] +
                   ( li_Real_s(  -7655486668943208827548357099520.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[20] +
                   ( li_Real_s(   3869555228022908364464815341568.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[21] +
                   ( li_Real_s(  -1112376806449043888485263474688.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[22] +
                   ( li_Real_s(    139573509546799548869910724608.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[23] +
                   ( li_Real_s(    832349260371318091771170258944.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[24] +
                   ( li_Real_s(  -4393289169234394446210669740032.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[25] +
                   ( li_Real_s(  10145709142968580763316392034304.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[26] +
                   ( li_Real_s( -13393334551995835574328705941504.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[27] +
                   ( li_Real_s(  10953096547821791574768949919744.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[28] +
                   ( li_Real_s(  -5536370690454111544936681701376.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[29] +
                   ( li_Real_s(   1591534423385496987685605081088.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[30] +
                   ( li_Real_s(   -199694962862831954239084822528.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[31] +
                   ( li_Real_s(   -721050713075074251472192405504.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[32] +
                   ( li_Real_s(   3805835409958116308790250831872.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[33] +
                   ( li_Real_s(  -8789063872839693050441738747904.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[34] +
                   ( li_Real_s(  11602429283568900250598866157568.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[35] +
                   ( li_Real_s(  -9488490536400118677796158439424.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[36] +
                   ( li_Real_s(   4796068461397810043108649336832.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[37] +
                   ( li_Real_s(  -1378720551890252529629875142656.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[38] +
                   ( li_Real_s(    172992519280310605020431122432.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[39] +
                   ( li_Real_s(    378961312367815408078527922176.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[40] +
                   ( li_Real_s(  -2000225997408631371884260229120.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[41] +
                   ( li_Real_s(   4619252321600500287665086660608.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[42] +
                   ( li_Real_s(  -6097867666585277595176610562048.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[43] +
                   ( li_Real_s(   4986848722612903724968426078208.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[44] +
                   ( li_Real_s(  -2520660982938753315590740377600.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[45] +
                   ( li_Real_s(    724611654251017775756188057600.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[46] +
                   ( li_Real_s(    -90919363899575300844710526976.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[47] +
                   ( li_Real_s(   -111981360793370080473566412800.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[48] +
                   ( li_Real_s(    591057772362141704772990795776.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[49] +
                   ( li_Real_s(  -1364968254049908168279956914176.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[50] +
                   ( li_Real_s(   1801892428345931410155767857152.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[51] +
                   ( li_Real_s(  -1473591334955993536971243782144.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[52] +
                   ( li_Real_s(    744843966525981948993702199296.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[53] +
                   ( li_Real_s(   -214119479936178108276460748800.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[54] +
                   ( li_Real_s(     26866262501395001602580938752.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[55] +
                   ( li_Real_s(     14339076688759688245427568640.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[56] +
                   ( li_Real_s(    -75684226962046552722315935744.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[57] +
                   ( li_Real_s(    174782520375156462300356935680.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[58] +
                   ( li_Real_s(   -230730128083605536769837105152.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[59] +
                   ( li_Real_s(    188691573438807308270976368640.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[60] +
                   ( li_Real_s(    -95376361600849943697591107584.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[61] +
                   ( li_Real_s(     27417738294626483868121694208.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[62] +
                   ( li_Real_s(     -3440192150857118454776856576.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[63];
        liVC[29] = ( li_Real_s(      6281881206521161059795992576.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 0] +
                   ( li_Real_s(    -33156899360887588285424074752.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 1] +
                   ( li_Real_s(     76571389666433800047415001088.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 2] +
                   ( li_Real_s(   -101081770051054568584127709184.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 3] +
                   ( li_Real_s(     82664879457417237204463255552.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 4] +
                   ( li_Real_s(    -41783929653696879405570195456.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 5] +
                   ( li_Real_s(     12011580526811823864421548032.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 6] +
                   ( li_Real_s(     -1507131791546612628427112448.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 7] +
                   ( li_Real_s(    -40285977329278577655171514368.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 8] +
                   ( li_Real_s(    212636637393010361853269770240.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 9] +
                   ( li_Real_s(   -491055651674317531216873521152.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[10] +
                   ( li_Real_s(    648241787088276396415159107584.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[11] +
                   ( li_Real_s(   -530133466938376483778469036032.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[12] +
                   ( li_Real_s(    267962158047259520374732226560.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[13] +
                   ( li_Real_s(    -77030788313755042453450129408.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[14] +
                   ( li_Real_s(      9665301727181513690965868544.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[15] +
                   ( li_Real_s(    110615734419413330160265461760.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[16] +
                   ( li_Real_s(   -583849750532392039867270299648.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[17] +
                   ( li_Real_s(   1348322298995706106148819042304.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[18] +
                   ( li_Real_s(  -1779918129148143776600730632192.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[19] +
                   ( li_Real_s(   1455620707629104433209439944704.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[20] +
                   ( li_Real_s(   -735760502775958866264900763648.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[21] +
                   ( li_Real_s(    211508266536344259845884477440.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[22] +
                   ( li_Real_s(    -26538625124073556582670008320.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[23] +
                   ( li_Real_s(   -168654854395196002990790017024.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[24] +
                   ( li_Real_s(    890190669468715638442336190464.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[25] +
                   ( li_Real_s(  -2055775358412595081928899559424.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[26] +
                   ( li_Real_s(   2713825791580023841068719013888.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[27] +
                   ( li_Real_s(  -2219372315450618308705608794112.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[28] +
                   ( li_Real_s(   1121807681266770777633061863424.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[29] +
                   ( li_Real_s(   -322484826483430195721200992256.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[30] +
                   ( li_Real_s(     40463212426331592798289002496.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[31] +
                   ( li_Real_s(    154315777748197560771271458816.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[32] +
                   ( li_Real_s(   -814506442803773514666395828224.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[33] +
                   ( li_Real_s(   1880992838912176891824248455168.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[34] +
                   ( li_Real_s(  -2483095664897597642139783659520.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[35] +
                   ( li_Real_s(   2030680743337904917913129713664.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[36] +
                   ( li_Real_s(  -1026431320408732435457775763456.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[37] +
                   ( li_Real_s(    295067088417176134028944736256.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[38] +
                   ( li_Real_s(    -37023020305352268515406512128.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[39] +
                   ( li_Real_s(    -84805396460547094873137741824.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[40] +
                   ( li_Real_s(    447618142576214668676517855232.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[41] +
                   ( li_Real_s(  -1033713764016289288826067615744.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[42] +
                   ( li_Real_s(   1364603901317541894180474716160.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[43] +
                   ( li_Real_s(  -1115975878017428223639865524224.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[44] +
                   ( li_Real_s(    564083053341521909035292426240.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[45] +
                   ( li_Real_s(   -162156338052085512219654094848.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[46] +
                   ( li_Real_s(     20346279311072544867928244224.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[47] +
                   ( li_Real_s(     25946900691806858332564619264.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[48] +
                   ( li_Real_s(   -136952410795774017869078069248.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[49] +
                   ( li_Real_s(    316273132375640830801306714112.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[50] +
                   ( li_Real_s(   -417511660734473992014519074816.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[51] +
                   ( li_Real_s(    341441895143140759911520010240.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[52] +
                   ( li_Real_s(   -172585797371782575947373346816.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[53] +
                   ( li_Real_s(     49613050305533556318932041728.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[54] +
                   ( li_Real_s(     -6225109614091498698190094336.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[55] +
                   ( li_Real_s(     -3414065880749525196701958144.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[56] +
                   ( li_Real_s(     18020054053823343136822263808.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[57] +
                   ( li_Real_s(    -41614885843901095597079265280.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[58] +
                   ( li_Real_s(     54935744841174681611873026048.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[59] +
                   ( li_Real_s(    -44926565157339186253667500032.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[60] +
                   ( li_Real_s(     22708657552572495232684261376.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[61] +
                   ( li_Real_s(     -6528032935982355993671499776.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[62] +
                   ( li_Real_s(       819093370399806325566472192.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[63];
        liVC[30] = ( li_Real_s(      -546250540399545818627964928.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 0] +
                   ( li_Real_s(      2883208644639107273652699136.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 1] +
                   ( li_Real_s(     -6658381722953610421872885760.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 2] +
                   ( li_Real_s(      8789719155003715477122842624.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 3] +
                   ( li_Real_s(     -7188250406550810986608066560.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 4] +
                   ( li_Real_s(      3633385197949240147670204416.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 5] +
                   ( li_Real_s(     -1044485266524925545901195264.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 6] +
                   ( li_Real_s(       131054938836817814296199168.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 7] +
                   ( li_Real_s(      3687191150165788971921047552.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 8] +
                   ( li_Real_s(    -19461658368869624332253396992.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 9] +
                   ( li_Real_s(     44944076681804489156242440192.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[10] +
                   ( li_Real_s(    -59330604379774703604684816384.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[11] +
                   ( li_Real_s(     48520690323898061199949955072.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[12] +
                   ( li_Real_s(    -24525350131436546257194057728.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[13] +
                   ( li_Real_s(      7050275563279266353921392640.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[14] +
                   ( li_Real_s(      -884620839066736023388028928.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[15] +
                   ( li_Real_s(    -10651885549806501700019683328.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[16] +
                   ( li_Real_s(     56222568655439118471668957184.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[17] +
                   ( li_Real_s(   -129838443847418357177854722048.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[18] +
                   ( li_Real_s(    171399523923037634052900257792.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[19] +
                   ( li_Real_s(   -140170883308480608901735120896.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[20] +
                   ( li_Real_s(     70851011575661167561135882240.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[21] +
                   ( li_Real_s(    -20367462764835513752350621696.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[22] +
                   ( li_Real_s(      2555571316403054849185284096.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[23] +
                   ( li_Real_s(     17070329411397028433505550336.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[24] +
                   ( li_Real_s(    -90100270313519309697333592064.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[25] +
                   ( li_Real_s(    208074429335800981184938246144.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[26] +
                   ( li_Real_s(   -274678724381738348985578422272.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[27] +
                   ( li_Real_s(    224632825950933932555005591552.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[28] +
                   ( li_Real_s(   -113543287857082288365685964800.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[29] +
                   ( li_Real_s(     32640164710495423771644526592.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[30] +
                   ( li_Real_s(     -4095466856287211638554099712.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[31] +
                   ( li_Real_s(    -16387516237303746479878307840.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[32] +
                   ( li_Real_s(     86496259517200259691373920256.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[33] +
                   ( li_Real_s(   -199751452207834598504195424256.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[34] +
                   ( li_Real_s(    263691575475502517759781109760.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[35] +
                   ( li_Real_s(   -215647512974977233853603643392.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[36] +
                   ( li_Real_s(    109001556376066295630072381440.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[37] +
                   ( li_Real_s(    -31334558131954947142920962048.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[38] +
                   ( li_Real_s(      3931648183301413316952326144.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[39] +
                   ( li_Real_s(      9422821837007310855497318400.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[40] +
                   ( li_Real_s(    -49735349226154737278165975040.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[41] +
                   ( li_Real_s(    114857085029388040003739713536.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[42] +
                   ( li_Real_s(   -151622655912028047910438436864.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[43] +
                   ( li_Real_s(    123997319971418804306264981504.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[44] +
                   ( li_Real_s(    -62675894921199105456700653568.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[45] +
                   ( li_Real_s(     18017370927091714014792646656.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[46] +
                   ( li_Real_s(     -2260697705523993653274476544.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[47] +
                   ( li_Real_s(     -3004377977017502077995188224.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[48] +
                   ( li_Real_s(     15857647579352096081111416832.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[49] +
                   ( li_Real_s(    -36621099574301561582736375808.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[50] +
                   ( li_Real_s(     48343455507118344519259521024.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[51] +
                   ( li_Real_s(    -39535377380567870318940520448.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[52] +
                   ( li_Real_s(     19983618669267299925474934784.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[53] +
                   ( li_Real_s(     -5744668990751718650830389248.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[54] +
                   ( li_Real_s(       720802166900924886479273984.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[55] +
                   ( li_Real_s(       409687905939994955799855104.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[56] +
                   ( li_Real_s(     -2162406487978773791218073600.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[57] +
                   ( li_Real_s(      4993786305224017518029438976.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[58] +
                   ( li_Real_s(     -6592289386687345175111401472.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[59] +
                   ( li_Real_s(      5391187823937517031201439744.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[60] +
                   ( li_Real_s(     -2725038909017127937948778496.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[61] +
                   ( li_Real_s(       783363953138066172256714752.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[62] +
                   ( li_Real_s(       -98291204556424312893997056.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[63];
        liVC[31] = ( li_Real_s(        19508947903483904710934528.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 0] +
                   ( li_Real_s(      -102971737515475161072009216.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 1] +
                   ( li_Real_s(       237799347825632301685932032.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 2] +
                   ( li_Real_s(      -313918542148980859612430336.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 3] +
                   ( li_Real_s(       256723229646129994580099072.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 4] +
                   ( li_Real_s(      -129763757540929266820055040.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 5] +
                   ( li_Real_s(        37303045379478226844254208.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 6] +
                   ( li_Real_s(        -4680533549333796303667200.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 7] +
                   ( li_Real_s(      -136562635401939598935326720.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 8] +
                   ( li_Real_s(       720802163176399203815391232.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 9] +
                   ( li_Real_s(     -1664595436480828306045796352.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[10] +
                   ( li_Real_s(      2197429797798480475638988800.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[11] +
                   ( li_Real_s(     -1797062610159593511811284992.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[12] +
                   ( li_Real_s(       908346304287608753874796544.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[13] +
                   ( li_Real_s(      -261121318129500044438536192.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[14] +
                   ( li_Real_s(        32763734909373332844445696.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[15] +
                   ( li_Real_s(       409687906329300068638654464.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[16] +
                   ( li_Real_s(     -2162406490427892511379816448.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[17] +
                   ( li_Real_s(      4993786312096772233164226560.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[18] +
                   ( li_Real_s(     -6592289397624637036855033856.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[19] +
                   ( li_Real_s(      5391187834460997796226924544.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[20] +
                   ( li_Real_s(     -2725038915097294748398911488.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[21] +
                   ( li_Real_s(       783363955084321325309755392.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[22] +
                   ( li_Real_s(       -98291204821565941294825472.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[23] +
                   ( li_Real_s(      -682813177272975847789166592.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[24] +
                   ( li_Real_s(      3604010817814137291120050176.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[25] +
                   ( li_Real_s(     -8322977188071650906536411136.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[26] +
                   ( li_Real_s(     10987148997905060125621616640.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[27] +
                   ( li_Real_s(     -8985313059065164152222777344.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[28] +
                   ( li_Real_s(      4541731526010252097683980288.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[29] +
                   ( li_Real_s(     -1305606592054046555014955008.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[30] +
                   ( li_Real_s(       163818674734380284916006912.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[31] +
                   ( li_Real_s(       682813177234291867628077056.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[32] +
                   ( li_Real_s(     -3604010817565487684300832768.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[33] +
                   ( li_Real_s(      8322977187287657334490267648.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[34] +
                   ( li_Real_s(    -10987148996480381128070397952.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[35] +
                   ( li_Real_s(      8985313057531723663475212288.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[36] +
                   ( li_Real_s(     -4541731525046936975240593408.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[37] +
                   ( li_Real_s(      1305606591727661476111974400.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[38] +
                   ( li_Real_s(      -163818674688528588453445632.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[39] +
                   ( li_Real_s(      -409687906282200632636997632.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[40] +
                   ( li_Real_s(      2162406490144367220361265152.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[41] +
                   ( li_Real_s(     -4993786311183809245714841600.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[42] +
                   ( li_Real_s(      6592289395884068348643770368.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[43] +
                   ( li_Real_s(     -5391187832506300318017912832.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[44] +
                   ( li_Real_s(      2725038913830980059863711744.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[45] +
                   ( li_Real_s(      -783363954646629110914220032.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[46] +
                   ( li_Real_s(        98291204759524331250253824.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[47] +
                   ( li_Real_s(       136562635400729053813014528.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[48] +
                   ( li_Real_s(      -720802163200685216649707520.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[49] +
                   ( li_Real_s(      1664595436525266167993991168.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[50] +
                   ( li_Real_s(     -2197429797742263545622429696.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[51] +
                   ( li_Real_s(      1797062609962606932724285440.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[52] +
                   ( li_Real_s(      -908346304099423215612329984.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[53] +
                   ( li_Real_s(       261121318051213991907164160.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[54] +
                   ( li_Real_s(       -32763734897445066202152960.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[55] +
                   ( li_Real_s(       -19508947909990324897841152.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[56] +
                   ( li_Real_s(       102971737570287464984084480.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[57] +
                   ( li_Real_s(      -237799347987347372387598336.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[58] +
                   ( li_Real_s(       313918542391200659871367168.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[59] +
                   ( li_Real_s(      -256723229854763356742746112.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[60] +
                   ( li_Real_s(       129763757647326773656944640.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[61] +
                   ( li_Real_s(       -37303045409974015064276992.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[62] +
                   ( li_Real_s(         4680533553264418302722048.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[63];
        liVC[32] = ( li_Real_s(     28470555544831819388765077504.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 0] +
                   ( li_Real_s(   -169298124946311482251205935104.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 1] +
                   ( li_Real_s(    433159166558720408262193184768.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 2] +
                   ( li_Real_s(   -619742986000919974431059607552.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 3] +
                   ( li_Real_s(    536873333275664382928237887488.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 4] +
                   ( li_Real_s(   -282163541654925955357260906496.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 5] +
                   ( li_Real_s(     83378055557014648772026695680.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 6] +
                   ( li_Real_s(    -10676458334073999044301029376.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 7] +
                   ( li_Real_s(             -96529322258775326720.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 8] +
                   ( li_Real_s(             639055772250643365888.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 9] +
                   ( li_Real_s(           -1822379581434691846144.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[10] +
                   ( li_Real_s(            2886591796916259389440.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[11] +
                   ( li_Real_s(           -2737391302317925466112.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[12] +
                   ( li_Real_s(            1554400060355362160640.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[13] +
                   ( li_Real_s(            -489907412994105802752.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[14] +
                   ( li_Real_s(              66159989483234197504.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[15] +
                   ( li_Real_s(             257788913374113628160.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[16] +
                   ( li_Real_s(           -1712789175370037329920.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[17] +
                   ( li_Real_s(            4893720893575547322368.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[18] +
                   ( li_Real_s(           -7757165234111761088512.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[19] +
                   ( li_Real_s(            7355899276986746404864.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[20] +
                   ( li_Real_s(           -4174977882008439488512.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[21] +
                   ( li_Real_s(            1314984957451949572096.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[22] +
                   ( li_Real_s(            -177461749898118397952.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[23] +
                   ( li_Real_s(            -381158554681180553216.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[24] +
                   ( li_Real_s(            2542275212372943568896.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[25] +
                   ( li_Real_s(           -7279743791380155072512.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[26] +
                   ( li_Real_s(           11550535088581581471744.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[27] +
                   ( li_Real_s(          -10954579312653667139584.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[28] +
                   ( li_Real_s(            6215316649400154980352.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[29] +
                   ( li_Real_s(           -1956516119939955294208.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[30] +
                   ( li_Real_s(             263870828300275482624.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[31] +
                   ( li_Real_s(             336839548648146272256.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[32] +
                   ( li_Real_s(           -2256117118500052140032.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[33] +
                   ( li_Real_s(            6476904583030083944448.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[34] +
                   ( li_Real_s(          -10289984268712282161152.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[35] +
                   ( li_Real_s(            9763026824616134836224.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[36] +
                   ( li_Real_s(           -5538509713990023643136.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[37] +
                   ( li_Real_s(            1742761980193445773312.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[38] +
                   ( li_Real_s(            -234921835285450194944.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[39] +
                   ( li_Real_s(            -178163201239907991552.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[40] +
                   ( li_Real_s(            1198682937649776295936.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[41] +
                   ( li_Real_s(           -3451146177890140291072.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[42] +
                   ( li_Real_s(            5491671172675507585024.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[43] +
                   ( li_Real_s(           -5213935211001404194816.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[44] +
                   ( li_Real_s(            2958086328191611830272.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[45] +
                   ( li_Real_s(            -930591345697243136000.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[46] +
                   ( li_Real_s(             125395497311798394880.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[47] +
                   ( li_Real_s(              52359586352026214400.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[48] +
                   ( li_Real_s(            -353904276103820410880.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[49] +
                   ( li_Real_s(            1022072457237670920192.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[50] +
                   ( li_Real_s(           -1629320345510262603776.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[51] +
                   ( li_Real_s(            1548258489254106890240.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[52] +
                   ( li_Real_s(            -878618459063709597696.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[53] +
                   ( li_Real_s(             276385628472437145600.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[54] +
                   ( li_Real_s(             -37233080638448394240.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[55] +
                   ( li_Real_s(              -6619012038598198272.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[56] +
                   ( li_Real_s(              44940321357802979328.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[57] +
                   ( li_Real_s(            -130186006738910216192.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[58] +
                   ( li_Real_s(             207918835723465031680.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[59] +
                   ( li_Real_s(            -197761329674698227712.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[60] +
                   ( li_Real_s(             112265925742315208704.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[61] +
                   ( li_Real_s(             -35315588305638576128.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[62] +
                   ( li_Real_s(               4756853934268361728.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[63];
        liVC[33] = ( li_Real_s(    -73820083256854596149579874304.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 0] +
                   ( li_Real_s(    438965852230809557328434561024.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 1] +
                   ( li_Real_s(  -1123119838180298335248770400256.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 2] +
                   ( li_Real_s(   1606905026769311476353920401408.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 3] +
                   ( li_Real_s(  -1392035855912321568078202667008.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 4] +
                   ( li_Real_s(    731609753853729135814263177216.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 5] +
                   ( li_Real_s(   -216187386733153498728176287744.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 6] +
                   ( li_Real_s(     27682531228779196500576043008.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 7] +
                   ( li_Real_s(    199293888719984172578952445952.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 8] +
                   ( li_Real_s(  -1185086874110640152720825122816.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 9] +
                   ( li_Real_s(   3032114164817453604306832850944.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[10] +
                   ( li_Real_s(  -4338200900848616640797386735616.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[11] +
                   ( li_Real_s(   3758113332300588728971484463104.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[12] +
                   ( li_Real_s(  -1975144791432307694919883948032.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[13] +
                   ( li_Real_s(    583646388894255771003647950848.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[14] +
                   ( li_Real_s(    -74735208340718606459472969728.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[15] +
                   ( li_Real_s(   -298940833249819297754615119872.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[16] +
                   ( li_Real_s(   1777630312468514464626166988800.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[17] +
                   ( li_Real_s(  -4548171251445421627458665316352.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[18] +
                   ( li_Real_s(   6507301358668384988492973735936.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[19] +
                   ( li_Real_s(  -5637170006009619154919600685056.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[20] +
                   ( li_Real_s(   2962717191661810618518648913920.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[21] +
                   ( li_Real_s(   -875469584804183953644707643392.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[22] +
                   ( li_Real_s(    112102812710335017670961790976.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[23] +
                   ( li_Real_s(    332156481636626256645494669312.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[24] +
                   ( li_Real_s(  -1975144793469847348958097047552.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[25] +
                   ( li_Real_s(   5053523618451428059863215767552.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[26] +
                   ( li_Real_s(  -7230334852691997385010691702784.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[27] +
                   ( li_Real_s(   6263522238587312531232710983680.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[28] +
                   ( li_Real_s(  -3291907996408190874064026337280.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[29] +
                   ( li_Real_s(    972743984928644462532882333696.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[30] +
                   ( li_Real_s(   -124558681033970090334140497920.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[31] +
                   ( li_Real_s(   -249117361414053719492964384768.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[32] +
                   ( li_Real_s(   1481358596475567166944763183104.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[33] +
                   ( li_Real_s(  -3790142718070117788927664324608.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[34] +
                   ( li_Real_s(   5422751146608045532307599130624.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[35] +
                   ( li_Real_s(  -4697641685923241874218589093888.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[36] +
                   ( li_Real_s(   2468931001357046718612256063488.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[37] +
                   ( li_Real_s(   -729557989981069943965615128576.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[38] +
                   ( li_Real_s(     93419010947822976354354200576.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[39] +
                   ( li_Real_s(    119576333559331806602405609472.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[40] +
                   ( li_Real_s(   -711052126901474471029713666048.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[41] +
                   ( li_Real_s(   1819268506492535836096531005440.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[42] +
                   ( li_Real_s(  -2602920553399026173356948848640.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[43] +
                   ( li_Real_s(   2254868012204959923780175527936.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[44] +
                   ( li_Real_s(  -1185086882358555028285288349696.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[45] +
                   ( li_Real_s(    350187835728984704871540195328.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[46] +
                   ( li_Real_s(    -44841125326755965360003874816.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[47] +
                   ( li_Real_s(    -33215648229713491802523172864.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[48] +
                   ( li_Real_s(    197514479833855534623189106688.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[49] +
                   ( li_Real_s(   -505352363340384480455720697856.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[50] +
                   ( li_Real_s(    723033487761504466809351307264.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[51] +
                   ( li_Real_s(   -626352226300378409144229560320.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[52] +
                   ( li_Real_s(    329190801049659400057182486528.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[53] +
                   ( li_Real_s(    -97274398937276656255269601280.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[54] +
                   ( li_Real_s(     12455868162733106203415543808.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[55] +
                   ( li_Real_s(      4067222233996099539087392768.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[56] +
                   ( li_Real_s(    -24185446523639676967501955072.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[57] +
                   ( li_Real_s(     61879881266425943047192707072.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[58] +
                   ( li_Real_s(    -88534712855195874745970065408.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[59] +
                   ( li_Real_s(     76696191041675951670401433600.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[60] +
                   ( li_Real_s(    -40309077717308621887155208192.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[61] +
                   ( li_Real_s(     11911150902049973704836775936.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[62] +
                   ( li_Real_s(     -1525208348005285848414158848.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[63];
        liVC[34] = ( li_Real_s(     74181614055614839434122362880.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 0] +
                   ( li_Real_s(   -441115669281578324473906462720.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 1] +
                   ( li_Real_s(   1128620270959843002638686748672.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 2] +
                   ( li_Real_s(  -1614774777392717401527991402496.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 3] +
                   ( li_Real_s(   1398853293677199516323991781376.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 4] +
                   ( li_Real_s(   -735192782215123949704693415936.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 5] +
                   ( li_Real_s(    217246155470399689396813037568.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 6] +
                   ( li_Real_s(    -27818105273638440812324847616.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 7] +
                   ( li_Real_s(   -317446693845246562128390782976.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 8] +
                   ( li_Real_s(   1887674090260306402441840033792.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 9] +
                   ( li_Real_s(  -4829724699828518207218012651520.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[10] +
                   ( li_Real_s(   6910134283785200402478875541504.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[11] +
                   ( li_Real_s(  -5986137657588867830471259586560.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[12] +
                   ( li_Real_s(   3146123485170606317082832273408.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[13] +
                   ( li_Real_s(   -929665318217627992248549376000.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[14] +
                   ( li_Real_s(    119042510264148455225083035648.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[15] +
                   ( li_Real_s(    625640457272508277969616109568.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[16] +
                   ( li_Real_s(  -3720326291102678988944448684032.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[17] +
                   ( li_Real_s(   9518672674707452086901534621696.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[18] +
                   ( li_Real_s( -13618852104812533174068188282880.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[19] +
                   ( li_Real_s(  11797791489952955603181264437248.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[20] +
                   ( li_Real_s(  -6200543824207671740838637993984.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[21] +
                   ( li_Real_s(   1832232769976872018797595197440.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[22] +
                   ( li_Real_s(   -234615171786903449680037806080.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[23] +
                   ( li_Real_s(   -750515477365533328766358519808.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[24] +
                   ( li_Real_s(   4462886679099829520731719335936.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[25] +
                   ( li_Real_s( -11418556912602169619468532056064.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[26] +
                   ( li_Real_s(  16337113711026415366348273090560.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[27] +
                   ( li_Real_s( -14152577592622595938993108418560.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[28] +
                   ( li_Real_s(   7438144475875521549524730380288.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[29] +
                   ( li_Real_s(  -2197938188016238284042993139712.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[30] +
                   ( li_Real_s(    281443304604763064473153961984.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[31] +
                   ( li_Real_s(    583646388309429441654895411200.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[32] +
                   ( li_Real_s(  -3470611560402793095690950017024.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[33] +
                   ( li_Real_s(   8879762915477120960858637205504.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[34] +
                   ( li_Real_s( -12704731220071129765588636794880.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[35] +
                   ( li_Real_s(  11005903342990079299471850602496.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[36] +
                   ( li_Real_s(  -5784352611755013587832814960640.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[37] +
                   ( li_Real_s(   1709250141686578006604749209600.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[38] +
                   ( li_Real_s(   -218867396234271822427684077568.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[39] +
                   ( li_Real_s(   -286129083155172757780176044032.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[40] +
                   ( li_Real_s(   1701446156037623072095857541120.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[41] +
                   ( li_Real_s(  -4353249626989310571702661414912.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[42] +
                   ( li_Real_s(   6228417017129640580445716348928.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[43] +
                   ( li_Real_s(  -5395577009055550349881364185088.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[44] +
                   ( li_Real_s(   2835743599975848831352144134144.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[45] +
                   ( li_Real_s(   -837949460494401310468113170432.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[46] +
                   ( li_Real_s(    107298406551323455916643188736.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[47] +
                   ( li_Real_s(     80587489173400998182622593024.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[48] +
                   ( li_Real_s(   -479207748403964402460977528832.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[49] +
                   ( li_Real_s(   1226081086833617597968540499968.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[50] +
                   ( li_Real_s(  -1754216955294975137874024857600.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[51] +
                   ( li_Real_s(   1519649799878637988823051534336.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[52] +
                   ( li_Real_s(   -798679582786631968972857147392.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[53] +
                   ( li_Real_s(    236006219158258973615522316288.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[54] +
                   ( li_Real_s(    -30220308558343248837412388864.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[55] +
                   ( li_Real_s(     -9964694443934056831946588160.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[56] +
                   ( li_Real_s(     59254343786516988699063877632.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[57] +
                   ( li_Real_s(   -151605708539999459370480959488.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[58] +
                   ( li_Real_s(    216910045603292684457076588544.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[59] +
                   ( li_Real_s(   -187905667207964018418946932736.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[60] +
                   ( li_Real_s(     98757239929668133998076887040.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[61] +
                   ( li_Real_s(    -29182319560021486221060472832.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[62] +
                   ( li_Real_s(      3736760432440371462310723584.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[63];
        liVC[35] = ( li_Real_s(    -38237537718980816083565412352.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 0] +
                   ( li_Real_s(    227376786787423823424357662720.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 1] +
                   ( li_Real_s(   -581756823868047542624022691840.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 2] +
                   ( li_Real_s(    832349258613616355979063984128.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 3] +
                   ( li_Real_s(   -721050711371803442988951011328.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 4] +
                   ( li_Real_s(    378961311400060105838460665856.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 5] +
                   ( li_Real_s(   -111981360490408816968818753536.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 6] +
                   ( li_Real_s(     14339076648148845842497798144.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 7] +
                   ( li_Real_s(    201824604537496193775991521280.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 8] +
                   ( li_Real_s(  -1200135594934113866099873284096.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 9] +
                   ( li_Real_s(   3070617198275383248907344543744.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[10] +
                   ( li_Real_s(  -4393289161211844199599453503488.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[11] +
                   ( li_Real_s(   3805835402040524703294717689856.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[12] +
                   ( li_Real_s(  -2000225992872126756786335121408.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[13] +
                   ( li_Real_s(    591057770934550232861188816896.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[14] +
                   ( li_Real_s(    -75684226769868562395069153280.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[15] +
                   ( li_Real_s(   -466086719177068284459270275072.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[16] +
                   ( li_Real_s(   2771551384213912591348405370880.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[17] +
                   ( li_Real_s(  -7091176516406940972852438892544.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[18] +
                   ( li_Real_s(  10145709126839814648016484171776.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[19] +
                   ( li_Real_s(  -8789063856549275856016901144576.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[20] +
                   ( li_Real_s(   4619252312173510941507682566144.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[21] +
                   ( li_Real_s(  -1364968251065672184596749352960.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[22] +
                   ( li_Real_s(    174782519971719715187113066496.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[23] +
                   ( li_Real_s(    615280338802461966082026504192.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[24] +
                   ( li_Real_s(  -3658720587217068937599927713792.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[25] +
                   ( li_Real_s(   9361050875341560264779611766784.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[26] +
                   ( li_Real_s( -13393334532613732138611134955520.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[27] +
                   ( li_Real_s(  11602429263514549002103328604160.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[28] +
                   ( li_Real_s(  -6097867654864164168985883967488.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[29] +
                   ( li_Real_s(   1801892424613230945400789139456.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[30] +
                   ( li_Real_s(   -230730127576844357071320121344.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[31] +
                   ( li_Real_s(   -503177526631699595775998689280.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[32] +
                   ( li_Real_s(   2992109222096941465649366958080.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[33] +
                   ( li_Real_s(  -7655486662056851464728120131584.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[34] +
                   ( li_Real_s(  10953096532764697523198497914880.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[35] +
                   ( li_Real_s(  -9488490520474430002793547825152.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[36] +
                   ( li_Real_s(   4986848713220641072587722457088.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[37] +
                   ( li_Real_s(  -1473591331948069745147974254592.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[38] +
                   ( li_Real_s(    188691573028768319288379441152.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[39] +
                   ( li_Real_s(    254336962863896148699986788352.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[40] +
                   ( li_Real_s(  -1512396583505914638288858120192.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[41] +
                   ( li_Real_s(   3869555224894548748456450588672.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[42] +
                   ( li_Real_s(  -5536370683122911128922923991040.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[43] +
                   ( li_Real_s(   4796068453488565859522447409152.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[44] +
                   ( li_Real_s(  -2520660978236987423316594655232.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[45] +
                   ( li_Real_s(    744843965012578537938261901312.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[46] +
                   ( li_Real_s(    -95376361393774274501421301760.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[47] +
                   ( li_Real_s(    -73113968357040291618825961472.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[48] +
                   ( li_Real_s(    434766990660930309262816575488.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[49] +
                   ( li_Real_s(  -1112376805657095041948904849408.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[50] +
                   ( li_Real_s(   1591534421380332303993674924032.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[51] +
                   ( li_Real_s(  -1378720549683860540662566879232.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[52] +
                   ( li_Real_s(    724611652929711747631539027968.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[53] +
                   ( li_Real_s(   -214119479508958344112282533888.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[54] +
                   ( li_Real_s(     27417738235978502856224276480.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[55] +
                   ( li_Real_s(      9173845680062868913410539520.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[56] +
                   ( li_Real_s(    -54551618096716860309767192576.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[57] +
                   ( li_Real_s(    139573509462968595427989913600.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[58] +
                   ( li_Real_s(   -199694962628405168041894084608.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[59] +
                   ( li_Real_s(    172992519016457545148606185472.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[60] +
                   ( li_Real_s(    -90919363740298076120242192384.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[61] +
                   ( li_Real_s(     26866262449653558900093353984.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[62] +
                   ( li_Real_s(     -3440192143726897149079715840.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[63];
        liVC[36] = ( li_Real_s(     11071882694002089869155762176.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 0] +
                   ( li_Real_s(    -65838159594483094538741088256.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 1] +
                   ( li_Real_s(    168450786731176557164426690560.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 2] +
                   ( li_Real_s(   -241011160869104687737575833600.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 3] +
                   ( li_Real_s(    208784073769399157562210779136.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 4] +
                   ( li_Real_s(   -109730266061690440576837615616.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 5] +
                   ( li_Real_s(     32424799344508793325998833664.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 6] +
                   ( li_Real_s(     -4151956013812253595904507904.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 7] +
                   ( li_Real_s(    -65838159637483164713711828992.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 8] +
                   ( li_Real_s(    391501913633641997167373582336.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 9] +
                   ( li_Real_s(  -1001680572085739517094823723008.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[10] +
                   ( li_Real_s(   1433155654635959820951450812416.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[11] +
                   ( li_Real_s(  -1241519583075734964965186994176.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[12] +
                   ( li_Real_s(    652503190149064860801362296832.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[13] +
                   ( li_Real_s(   -192811753525133115754689855488.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[14] +
                   ( li_Real_s(     24689309905424584985527975936.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[15] +
                   ( li_Real_s(    168450786927534380527082536960.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[16] +
                   ( li_Real_s(  -1001680572582051677154771468288.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[17] +
                   ( li_Real_s(   2562858402922880143974656376832.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[18] +
                   ( li_Real_s(  -3666812669610992797321460187136.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[19] +
                   ( li_Real_s(   3176500558455874628143175172096.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[20] +
                   ( li_Real_s(  -1669467623675185066720396050432.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[21] +
                   ( li_Real_s(    493320162810653327633628004352.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[22] +
                   ( li_Real_s(    -63169045248714698300518825984.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[23] +
                   ( li_Real_s(   -241011161237939012276336984064.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[24] +
                   ( li_Real_s(   1433155655822991870610978635776.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[25] +
                   ( li_Real_s(  -3666812670771383521910301130752.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[26] +
                   ( li_Real_s(   5246296535272846366382275690496.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[27] +
                   ( li_Real_s(  -4544781906585050127999663341568.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[28] +
                   ( li_Real_s(   2388592764485239294923403952128.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[29] +
                   ( li_Real_s(   -705818402720067640831225364480.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[30] +
                   ( li_Real_s(     90379185733363298866449874944.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[31] +
                   ( li_Real_s(    208784074143021828851657342976.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[32] +
                   ( li_Real_s(  -1241519584377164778346901405696.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[33] +
                   ( li_Real_s(   3176500560077655756856402903040.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[34] +
                   ( li_Real_s(  -4544781907418209866613717467136.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[35] +
                   ( li_Real_s(   3937071121483935950414333083648.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[36] +
                   ( li_Real_s(  -2069199312071888284509383163904.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[37] +
                   ( li_Real_s(    611439076236127225344230948864.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[38] +
                   ( li_Real_s(    -78294028073479001876994195456.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[39] +
                   ( li_Real_s(   -109730266279680038112172441600.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[40] +
                   ( li_Real_s(    652503190936930490588067790848.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[41] +
                   ( li_Real_s(  -1669467624748241987335268335616.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[42] +
                   ( li_Real_s(   2388592765206063214757165400064.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[43] +
                   ( li_Real_s(  -2069199312309045870561876508672.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[44] +
                   ( li_Real_s(   1087505320999248417299818872832.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[45] +
                   ( li_Real_s(   -321352923816782931256955371520.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[46] +
                   ( li_Real_s(     41148850011508458330615971840.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[47] +
                   ( li_Real_s(     32424799414233764649506963456.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[48] +
                   ( li_Real_s(   -192811753783554341894696730624.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[49] +
                   ( li_Real_s(    493320163182356867347489226752.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[50] +
                   ( li_Real_s(   -705818403003567970736802889728.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[51] +
                   ( li_Real_s(    611439076365941373540860166144.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[52] +
                   ( li_Real_s(   -321352923848557163634193596416.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[53] +
                   ( li_Real_s(     94958341502953122127962701824.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[54] +
                   ( li_Real_s(    -12159299829805444691939819520.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[55] +
                   ( li_Real_s(     -4151956023357579679802327040.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[56] +
                   ( li_Real_s(     24689309941584210694057754624.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[57] +
                   ( li_Real_s(    -63169045303045244595814268928.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[58] +
                   ( li_Real_s(     90379185778558222948880089088.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[59] +
                   ( li_Real_s(    -78294028097755286232427921408.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[60] +
                   ( li_Real_s(     41148850019697172333547487232.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[61] +
                   ( li_Real_s(    -12159299831037379301141905408.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[62] +
                   ( li_Real_s(      1556983515359762085090164736.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[63];
        liVC[37] = ( li_Real_s(     -1818952159102491860272152576.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 0] +
                   ( li_Real_s(     10816269091079236744906801152.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 1] +
                   ( li_Real_s(    -27674057862853658583444226048.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 2] +
                   ( li_Real_s(     39594690782665691883523538944.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 3] +
                   ( li_Real_s(    -34300240756242404266867687424.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 4] +
                   ( li_Real_s(     18027115176110845347560947712.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 5] +
                   ( li_Real_s(     -5326931332642000023666556928.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 6] +
                   ( li_Real_s(       682107060982534593442742272.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 7] +
                   ( li_Real_s(     11665019291683287326414340096.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 8] +
                   ( li_Real_s(    -69365204027395923308944818176.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 9] +
                   ( li_Real_s(    177474936510961958917997854720.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[10] +
                   ( li_Real_s(   -253922473845160601682089869312.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[11] +
                   ( li_Real_s(    219968935615626020231829258240.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[12] +
                   ( li_Real_s(   -115608673599633526206702288896.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[13] +
                   ( li_Real_s(     34161842300696368132650958848.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[14] +
                   ( li_Real_s(     -4374382246777638386736824320.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[15] +
                   ( li_Real_s(    -32029375027056558517340078080.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[16] +
                   ( li_Real_s(    190460390877962915900580429824.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[17] +
                   ( li_Real_s(   -487304063425215150239682396160.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[18] +
                   ( li_Real_s(    697210861127461664731045036032.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[19] +
                   ( li_Real_s(   -603982501882435175494763675648.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[20] +
                   ( li_Real_s(    317433985533254334933649850368.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[21] +
                   ( li_Real_s(    -93800312881034034137800900608.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[22] +
                   ( li_Real_s(     12011015677062035809660567552.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[23] +
                   ( li_Real_s(     48834911332334966551015849984.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[24] +
                   ( li_Real_s(   -290393312195666161338406666240.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[25] +
                   ( li_Real_s(    742988294751466368957161668608.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[26] +
                   ( li_Real_s(  -1063031375502621181389773471744.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[27] +
                   ( li_Real_s(    920886901792022396487665188864.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[28] +
                   ( li_Real_s(   -483988854919959010510165245952.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[29] +
                   ( li_Real_s(    143016526564125219823640641536.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[30] +
                   ( li_Real_s(    -18313091821701600224579944448.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[31] +
                   ( li_Real_s(    -44682955325390240042211868672.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[32] +
                   ( li_Real_s(    265704002371311647301360943104.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[33] +
                   ( li_Real_s(   -679819249793029495788947898368.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[34] +
                   ( li_Real_s(    972652190273874645111770447872.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[35] +
                   ( li_Real_s(   -842592874212053268967324647424.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[36] +
                   ( li_Real_s(    442840005188772466648110071808.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[37] +
                   ( li_Real_s(   -130857226821308253289710616576.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[38] +
                   ( li_Real_s(     16756108317822516619139612672.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[39] +
                   ( li_Real_s(     24555854216770152319703580672.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[40] +
                   ( li_Real_s(   -146019633209776766145410367488.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[41] +
                   ( li_Real_s(    373599782546525278096009986048.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[42] +
                   ( li_Real_s(   -534528327791245896972675055616.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[43] +
                   ( li_Real_s(    463053252311264130861853835264.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[44] +
                   ( li_Real_s(   -243366056058860366160717676544.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[45] +
                   ( li_Real_s(     71913573357199951913568698368.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[46] +
                   ( li_Real_s(     -9208445371876525693774856192.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[47] +
                   ( li_Real_s(     -7513063288432516366170324992.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[48] +
                   ( li_Real_s(     44675894229178234427297234944.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[49] +
                   ( li_Real_s(   -114305891630110953883425570816.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[50] +
                   ( li_Real_s(    163543288742308252337555111936.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[51] +
                   ( li_Real_s(   -141674908156824375914171203584.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[52] +
                   ( li_Real_s(     74459823937876981086702010368.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[53] +
                   ( li_Real_s(    -22002542579877761744193454080.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[54] +
                   ( li_Real_s(      2817398745882102673010851840.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[55] +
                   ( li_Real_s(       988560959124427399816544256.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[56] +
                   ( li_Real_s(     -5878407136263973824318406656.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[57] +
                   ( li_Real_s(     15040248901100921223584415744.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[58] +
                   ( li_Real_s(    -21518853785557207178910105600.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[59] +
                   ( li_Real_s(     18641435287094146875451768832.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[60] +
                   ( li_Real_s(     -9797345256727506974746345472.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[61] +
                   ( li_Real_s(      2895071392590192309308489728.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[62] +
                   ( li_Real_s(      -370710361360858130625331200.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[63];
        liVC[38] = ( li_Real_s(       158169753275240880220930048.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 0] +
                   ( li_Real_s(      -940545140384208766229282816.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 1] +
                   ( li_Real_s(      2406439819894135326425219072.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 2] +
                   ( li_Real_s(     -3443016598819766237606707200.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 3] +
                   ( li_Real_s(      2982629639491921930828644352.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 4] +
                   ( li_Real_s(     -1567575237511525461731049472.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 5] +
                   ( li_Real_s(       463211421730769654610132992.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 6] +
                   ( li_Real_s(       -59313657676727125071101952.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 7] +
                   ( li_Real_s(     -1067645835575767566336917504.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 8] +
                   ( li_Real_s(      6348679704422443009894776832.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 9] +
                   ( li_Real_s(    -16243468804313757381038178304.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[10] +
                   ( li_Real_s(     23240362074036972199585251328.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[11] +
                   ( li_Real_s(    -20132750096890516070446661632.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[12] +
                   ( li_Real_s(     10581132870315621130157686784.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[13] +
                   ( li_Real_s(     -3126677102029385520300163072.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[14] +
                   ( li_Real_s(       400367190034392603665891328.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[15] +
                   ( li_Real_s(      3084310193565213038997405696.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[16] +
                   ( li_Real_s(    -18340630270484594019402776576.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[17] +
                   ( li_Real_s(     46925576584214404100872208384.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[18] +
                   ( li_Real_s(    -67138823830135625167633645568.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[19] +
                   ( li_Real_s(     58161278114599814245642141696.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[20] +
                   ( li_Real_s(    -30567717212733843292261711872.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[21] +
                   ( li_Real_s(      9032622749051072057675087872.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[22] +
                   ( li_Real_s(     -1156616328076442475717197824.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[23] +
                   ( li_Real_s(     -4942804799201536630167961600.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[24] +
                   ( li_Real_s(     29392035702445304995540631552.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[25] +
                   ( li_Real_s(    -75201244561788797658798751744.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[26] +
                   ( li_Real_s(    107594269014095473263431909376.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[27] +
                   ( li_Real_s(    -93207176516845985773146603520.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[28] +
                   ( li_Real_s(     48986726330542647038586126336.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[29] +
                   ( li_Real_s(    -14475356978181692383123472384.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[30] +
                   ( li_Real_s(      1853551808934628929119977472.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[31] +
                   ( li_Real_s(      4745092608180924334615822336.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[32] +
                   ( li_Real_s(    -28216354280769205938868453376.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[33] +
                   ( li_Real_s(     72193194797039030968545968128.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[34] +
                   ( li_Real_s(   -103290498279969357590679257088.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[35] +
                   ( li_Real_s(     89478889479493716834772844544.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[36] +
                   ( li_Real_s(    -47027257289564712801113473024.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[37] +
                   ( li_Real_s(     13896342702613688258756870144.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[38] +
                   ( li_Real_s(     -1779409737024063175309393920.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[39] +
                   ( li_Real_s(     -2728428249946823780879826944.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[40] +
                   ( li_Real_s(     16224403713039975399326482432.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[41] +
                   ( li_Real_s(    -41511087012383898058115514368.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[42] +
                   ( li_Real_s(     59392036516434443601191108608.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[43] +
                   ( li_Real_s(    -51450361454855951690263166976.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[44] +
                   ( li_Real_s(     27040672943290932169933848576.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[45] +
                   ( li_Real_s(     -7990397054403094850465431552.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[46] +
                   ( li_Real_s(      1023160598824412673787035648.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[47] +
                   ( li_Real_s(       869933644921245638712098816.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[48] +
                   ( li_Real_s(     -5172998285374520890746732544.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[49] +
                   ( li_Real_s(     13235419047443130597846810624.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[50] +
                   ( li_Real_s(    -18936591352792877694367825920.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[51] +
                   ( li_Real_s(     16404463072010273607749992448.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[52] +
                   ( li_Real_s(     -8621663836518077264690151424.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[53] +
                   ( li_Real_s(      2547662828745121472649887744.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[54] +
                   ( li_Real_s(      -326225118434298559530532864.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[55] +
                   ( li_Real_s(      -118627315211587099488681984.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[56] +
                   ( li_Real_s(       705408857060969781397553152.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[57] +
                   ( li_Real_s(     -1804829869986200479089033216.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[58] +
                   ( li_Real_s(      2582262456974063699681607680.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[59] +
                   ( li_Real_s(     -2236972236844756768638631936.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[60] +
                   ( li_Real_s(      1175681432093446713047515136.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[61] +
                   ( li_Real_s(      -347408567500786607755100160.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[62] +
                   ( li_Real_s(        44485243414841603974496256.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[63];
        liVC[39] = ( li_Real_s(        -5648919773948703022252032.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 0] +
                   ( li_Real_s(        33590897962393652860813312.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 1] +
                   ( li_Real_s(       -85944279538100136723873792.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 2] +
                   ( li_Real_s(       122964878928978314277158912.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 3] +
                   ( li_Real_s(      -106522487499174602325622784.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 4] +
                   ( li_Real_s(        55984830121364187892416512.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 5] +
                   ( li_Real_s(       -16543265127247981574094848.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 6] +
                   ( li_Real_s(         2118344925732192613564416.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 7] +
                   ( li_Real_s(        39542438446889580795789312.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 8] +
                   ( li_Real_s(      -235136285949300771221667840.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 9] +
                   ( li_Real_s(       601609957397235141468749824.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[10] +
                   ( li_Real_s(      -860754153513733126023544832.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[11] +
                   ( li_Real_s(       745657413451672165743067136.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[12] +
                   ( li_Real_s(      -391893811389345048435884032.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[13] +
                   ( li_Real_s(       115802856059355406591328256.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[14] +
                   ( li_Real_s(       -14828414502773353212805120.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[15] +
                   ( li_Real_s(      -118627315385343214083899392.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[16] +
                   ( li_Real_s(       705408858170250295108435968.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[17] +
                   ( li_Real_s(     -1804829873131213852365553664.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[18] +
                   ( li_Real_s(      2582262462014837979139276800.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[19] +
                   ( li_Real_s(     -2236972241719589454697463808.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[20] +
                   ( li_Real_s(      1175681434921011700492664832.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[21] +
                   ( li_Real_s(      -347408568408873467293728768.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[22] +
                   ( li_Real_s(        44485243538919223426285568.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[23] +
                   ( li_Real_s(       197712192326221261921320960.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[24] +
                   ( li_Real_s(     -1175681430412699153968660480.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[25] +
                   ( li_Real_s(      3008049788901920031201296384.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[26] +
                   ( li_Real_s(     -4303770770507140691918848000.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[27] +
                   ( li_Real_s(      3728287069909457498437320704.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[28] +
                   ( li_Real_s(     -1959469058371357991522795520.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[29] +
                   ( li_Real_s(       579014280723035047977811968.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[30] +
                   ( li_Real_s(       -74142072569436431624175616.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[31] +
                   ( li_Real_s(      -197712192307221185597276160.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[32] +
                   ( li_Real_s(      1175681430283833917292150784.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[33] +
                   ( li_Real_s(     -3008049788488754897564467200.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[34] +
                   ( li_Real_s(      4303770769757037916531458048.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[35] +
                   ( li_Real_s(     -3728287069105890970149322752.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[36] +
                   ( li_Real_s(      1959469057868205802611802112.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[37] +
                   ( li_Real_s(      -579014280552613013415264256.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[38] +
                   ( li_Real_s(        74142072545402421700984832.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[39] +
                   ( li_Real_s(       118627315359803053619281920.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[40] +
                   ( li_Real_s(      -705408858001331911416348672.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[41] +
                   ( li_Real_s(      1804829872578514370972090368.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[42] +
                   ( li_Real_s(     -2582262460979603251367247872.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[43] +
                   ( li_Real_s(      2236972240580223279193653248.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[44] +
                   ( li_Real_s(     -1175681434193101330361352192.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[45] +
                   ( li_Real_s(       347408568158906714263912448.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[46] +
                   ( li_Real_s(       -44485243503410787465035776.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[47] +
                   ( li_Real_s(       -39542438442410316453117952.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[48] +
                   ( li_Real_s(       235136285925915258410500096.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[49] +
                   ( li_Real_s(      -601609957303176938234314752.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[50] +
                   ( li_Real_s(       860754153288963537370087424.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[51] +
                   ( li_Real_s(      -745657413159443552995901440.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[52] +
                   ( li_Real_s(       391893811181827828014383104.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[53] +
                   ( li_Real_s(      -115802855983284217154895872.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[54] +
                   ( li_Real_s(        14828414491608607201689600.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[55] +
                   ( li_Real_s(         5648919775720087121559552.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[56] +
                   ( li_Real_s(       -33590897977291949517832192.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[57] +
                   ( li_Real_s(        85944279578808300611829760.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[58] +
                   ( li_Real_s(      -122964878982202631340949504.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[59] +
                   ( li_Real_s(       106522487536336824034131968.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[60] +
                   ( li_Real_s(       -55984830135144212504510464.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[61] +
                   ( li_Real_s(        16543265129681029007671296.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[62] +
                   ( li_Real_s(        -2118344925906689618608128.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[63];
        liVC[40] = ( li_Real_s(     -4677305554648781246120853504.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 0] +
                   ( li_Real_s(     29995763883770250879561629696.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 1] +
                   ( li_Real_s(    -82361249988352106049294041088.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 2] +
                   ( li_Real_s(    125575486097236994023495827456.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 3] +
                   ( li_Real_s(   -114899027768574824196457103360.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 4] +
                   ( li_Real_s(     63143624996771992402929909760.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 5] +
                   ( li_Real_s(    -19319305555094462501501272064.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 6] +
                   ( li_Real_s(      2542013888890977919071944704.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 7] +
                   ( li_Real_s(              21090943915039211520.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 8] +
                   ( li_Real_s(            -140091038057247178752.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 9] +
                   ( li_Real_s(             400437491691413110784.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[10] +
                   ( li_Real_s(            -635310267494301564928.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[11] +
                   ( li_Real_s(             603151307540106182656.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[12] +
                   ( li_Real_s(            -342778556674660433920.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[13] +
                   ( li_Real_s(             108108350346920787968.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[14] +
                   ( li_Real_s(             -14608231267270297600.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[15] +
                   ( li_Real_s(             -56143662758310952960.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[16] +
                   ( li_Real_s(             374296155297385218048.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[17] +
                   ( li_Real_s(           -1072051129796470636544.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[18] +
                   ( li_Real_s(            1702258935679242469376.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[19] +
                   ( li_Real_s(           -1616171628309948923904.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[20] +
                   ( li_Real_s(             918128516141940736000.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[21] +
                   ( li_Real_s(            -289397516418843803648.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[22] +
                   ( li_Real_s(              39080330165006131200.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[23] +
                   ( li_Real_s(              82839093852370370560.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[24] +
                   ( li_Real_s(            -554433421696900464640.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[25] +
                   ( li_Real_s(            1591584964103665614848.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[26] +
                   ( li_Real_s(           -2529800014777659949056.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[27] +
                   ( li_Real_s(            2402336713283485040640.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[28] +
                   ( li_Real_s(           -1364340077764169957376.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[29] +
                   ( li_Real_s(             429821396289466204160.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[30] +
                   ( li_Real_s(             -58008653290254876672.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[31] +
                   ( li_Real_s(             -73117005156844740608.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[32] +
                   ( li_Real_s(             491433831808354811904.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[33] +
                   ( li_Real_s(           -1414381012131582050304.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[34] +
                   ( li_Real_s(            2251099078371388162048.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[35] +
                   ( li_Real_s(           -2138609139263769411584.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[36] +
                   ( li_Real_s(            1214436426895229976576.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[37] +
                   ( li_Real_s(            -382452894665934831616.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[38] +
                   ( li_Real_s(              51590714143158329344.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[39] +
                   ( li_Real_s(              38647231250016149504.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[40] +
                   ( li_Real_s(            -260926935480367579136.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[41] +
                   ( li_Real_s(             753138287647386894336.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[42] +
                   ( li_Real_s(           -1200603509555660062720.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[43] +
                   ( li_Real_s(            1141388465252707729408.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[44] +
                   ( li_Real_s(            -648218630760065007616.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[45] +
                   ( li_Real_s(             204096860665078415360.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[46] +
                   ( li_Real_s(             -27521769019096891392.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[47] +
                   ( li_Real_s(             -11353633934495985664.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[48] +
                   ( li_Real_s(              77009759074367799296.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[49] +
                   ( li_Real_s(            -222965866061622018048.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[50] +
                   ( li_Real_s(             356079758930086985728.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[51] +
                   ( li_Real_s(            -338813299025847779328.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[52] +
                   ( li_Real_s(             192471443480176918528.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[53] +
                   ( li_Real_s(             -60597653976519901184.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[54] +
                   ( li_Real_s(               8169491513853970432.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[55] +
                   ( li_Real_s(               1434932913270953728.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[56] +
                   ( li_Real_s(              -9777022625063702528.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[57] +
                   ( li_Real_s(              28394518066910150656.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[58] +
                   ( li_Real_s(             -45430803398039830528.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[59] +
                   ( li_Real_s(              43269143741296754688.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[60] +
                   ( li_Real_s(             -24589003153747103744.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[61] +
                   ( li_Real_s(               7741809244047161344.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[62] +
                   ( li_Real_s(              -1043574788676297216.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[63];
        liVC[41] = ( li_Real_s(     12127585104602263114158702592.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 0] +
                   ( li_Real_s(    -77774730565284982952151744512.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 1] +
                   ( li_Real_s(    213550955123581242889788719104.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 2] +
                   ( li_Real_s(   -325599295794964907700787347456.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 3] +
                   ( li_Real_s(    297916764591062966621154836480.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 4] +
                   ( li_Real_s(   -163722398956141461529643974656.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 5] +
                   ( li_Real_s(     50092199360542733513921658880.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 6] +
                   ( li_Real_s(     -6591078863398668694557032448.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 7] +
                   ( li_Real_s(    -32741138851699237376892076032.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 8] +
                   ( li_Real_s(    209970347011516098618786316288.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 9] +
                   ( li_Real_s(   -576528749514201619884564021248.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[10] +
                   ( li_Real_s(    879028402182759701448340013056.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[11] +
                   ( li_Real_s(   -804293194023476847916649283584.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[12] +
                   ( li_Real_s(    442005374826220315149030391808.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[13] +
                   ( li_Real_s(   -135235138849295490755166470144.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[14] +
                   ( li_Real_s(     17794097218177146687812796416.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[15] +
                   ( li_Real_s(     49111708299756998631343783936.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[16] +
                   ( li_Real_s(   -314955520710300873271139106816.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[17] +
                   ( li_Real_s(    864793124947812864467746684928.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[18] +
                   ( li_Real_s(  -1318542604520486331093065138176.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[19] +
                   ( li_Real_s(   1206439792350776466093702643712.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[20] +
                   ( li_Real_s(   -663008063041761377023864864768.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[21] +
                   ( li_Real_s(    202852708537724291187094847488.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[22] +
                   ( li_Real_s(    -26691145863522258894144405504.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[23] +
                   ( li_Real_s(    -54568564817299745158396379136.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[24] +
                   ( li_Real_s(    349950578879539525441709670400.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[25] +
                   ( li_Real_s(   -960881250953986859847066320896.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[26] +
                   ( li_Real_s(   1465047340115149083142028001280.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[27] +
                   ( li_Real_s(  -1340488659948263239107202777088.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[28] +
                   ( li_Real_s(    736675626656253996111654551552.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[29] +
                   ( li_Real_s(   -225391898714667670049621278720.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[30] +
                   ( li_Real_s(     29656828783275674726987464704.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[31] +
                   ( li_Real_s(     40926423645116300119945248768.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[32] +
                   ( li_Real_s(   -262462934406140046979176071168.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[33] +
                   ( li_Real_s(    720660938994713085512104542208.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[34] +
                   ( li_Real_s(  -1098785506413344768548958896128.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[35] +
                   ( li_Real_s(   1005366496282447303197197336576.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[36] +
                   ( li_Real_s(   -552506720764213413359403401216.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[37] +
                   ( li_Real_s(    169043924281973809404845228032.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[38] +
                   ( li_Real_s(    -22242621620552115414926098432.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[39] +
                   ( li_Real_s(    -19644683364156338831647309824.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[40] +
                   ( li_Real_s(    125982208625312082470937559040.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[41] +
                   ( li_Real_s(   -345917251062580751277829914624.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[42] +
                   ( li_Real_s(    527417043659783541496064507904.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[43] +
                   ( li_Real_s(   -482575918788808254343348224000.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[44] +
                   ( li_Real_s(    265203226298895067017451143168.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[45] +
                   ( li_Real_s(    -81141083760346409216296091648.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[46] +
                   ( li_Real_s(     10676458391900622880017219584.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[47] +
                   ( li_Real_s(      5456856493539530282423549952.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[48] +
                   ( li_Real_s(    -34995057978097734404781637632.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[49] +
                   ( li_Real_s(     96088125378016387768938135552.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[50] +
                   ( li_Real_s(   -146504734488645569058109915136.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[51] +
                   ( li_Real_s(    134048866466099441131157716992.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[52] +
                   ( li_Real_s(    -73667562939008556561185374208.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[53] +
                   ( li_Real_s(     22539189958000214474840080384.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[54] +
                   ( li_Real_s(     -2965682889903578943108153344.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[55] +
                   ( li_Real_s(      -668186509755246532674715648.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[56] +
                   ( li_Real_s(      4285109142801925616695246848.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[57] +
                   ( li_Real_s(    -11765892911607346598860816384.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[58] +
                   ( li_Real_s(     17939355257157798164843986944.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[59] +
                   ( li_Real_s(    -16414146927531871720519499776.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[60] +
                   ( li_Real_s(      9020517918522841377340915712.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[61] +
                   ( li_Real_s(     -2759900813564508307510525952.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[62] +
                   ( li_Real_s(       363144843976143087102590976.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[63];
        liVC[42] = ( li_Real_s(    -12186979445941668495044378624.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 0] +
                   ( li_Real_s(     78155629061553214421985132544.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 1] +
                   ( li_Real_s(   -214596812022222665177989382144.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 2] +
                   ( li_Real_s(    327193904787142116308309508096.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 3] +
                   ( li_Real_s(   -299375799553576251981536690176.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 4] +
                   ( li_Real_s(    164524222600888787949907345408.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 5] +
                   ( li_Real_s(    -50337523826246295422861574144.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 6] +
                   ( li_Real_s(      6623358398398606243277045760.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 7] +
                   ( li_Real_s(     52151956813921439126663462912.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 8] +
                   ( li_Real_s(   -334452766579571163946607968256.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 9] +
                   ( li_Real_s(    918327935533750500608735969280.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[10] +
                   ( li_Real_s(  -1400166667419168891852982059008.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[11] +
                   ( li_Real_s(   1281124157465027194721574846464.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[12] +
                   ( li_Real_s(   -704051417613167611388501164032.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[13] +
                   ( li_Real_s(    215410256619093852117536866304.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[14] +
                   ( li_Real_s(    -28343454819885222629396709376.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[15] +
                   ( li_Real_s(   -102783789336105111427376742400.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[16] +
                   ( li_Real_s(    659156910059378919897942720512.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[17] +
                   ( li_Real_s(  -1809888465470966276207883059200.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[18] +
                   ( li_Real_s(   2759521303134621655898074906624.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[19] +
                   ( li_Real_s(  -2524906132302095213921279410176.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[20] +
                   ( li_Real_s(   1387581157969257829251181182976.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[21] +
                   ( li_Real_s(   -424541739219223169046149070848.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[22] +
                   ( li_Real_s(     55860755165131321575024361472.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[23] +
                   ( li_Real_s(    123298971188293785850979811328.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[24] +
                   ( li_Real_s(   -790721663379204935074231353344.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[25] +
                   ( li_Real_s(   2171134059703487641272203608064.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[26] +
                   ( li_Real_s(  -3310309339311377599122877972480.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[27] +
                   ( li_Real_s(   3028866036264946066694044909568.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[28] +
                   ( li_Real_s(  -1664536114221302382595170893824.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[29] +
                   ( li_Real_s(    509278360332578270117793628160.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[30] +
                   ( li_Real_s(    -67010310577418648119486185472.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[31] +
                   ( li_Real_s(    -95884763721639520067674701824.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[32] +
                   ( li_Real_s(    614913158973581080340763508736.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[33] +
                   ( li_Real_s(  -1688405623848619283239611138048.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[34] +
                   ( li_Real_s(   2574297464825552003566026096640.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[35] +
                   ( li_Real_s(  -2355430070072531198185333325824.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[36] +
                   ( li_Real_s(   1294444313298948918057193439232.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[37] +
                   ( li_Real_s(   -396045764228826350601132572672.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[38] +
                   ( li_Real_s(     52111284773533637646233894912.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[39] +
                   ( li_Real_s(     47006920770460431257725566976.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[40] +
                   ( li_Real_s(   -301457426870006564494501740544.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[41] +
                   ( li_Real_s(    827730562430979532350017241088.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[42] +
                   ( li_Real_s(  -1262033636045726368120606556160.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[43] +
                   ( li_Real_s(   1154735230323516623949662257152.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[44] +
                   ( li_Real_s(   -634593432136217696013268287488.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[45] +
                   ( li_Real_s(    194159021156250850880317816832.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[46] +
                   ( li_Real_s(    -25547239629256550324602142720.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[47] +
                   ( li_Real_s(    -13239373212587606479848079360.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[48] +
                   ( li_Real_s(     84904676098195085924612702208.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[49] +
                   ( li_Real_s(   -233128093855766631022482948096.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[50] +
                   ( li_Real_s(    355448390242631658895201796096.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[51] +
                   ( li_Real_s(   -325228081939260028416811859968.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[52] +
                   ( li_Real_s(    178731538911827694715769192448.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[53] +
                   ( li_Real_s(    -54684367798440488061791895552.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[54] +
                   ( li_Real_s(      7195311553400289156583653376.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[55] +
                   ( li_Real_s(      1637056943370030103555735552.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[56] +
                   ( li_Real_s(    -10498517362514583220503183360.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[57] +
                   ( li_Real_s(     28826437525573678342948782080.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[58] +
                   ( li_Real_s(    -43951420208043519128467668992.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[59] +
                   ( li_Real_s(     40214659808943781691720204288.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[60] +
                   ( li_Real_s(    -22100268807535170205618536448.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[61] +
                   ( li_Real_s(      6761756964005308816638869504.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[62] +
                   ( li_Real_s(      -889704863800096634492157952.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[63];
        liVC[43] = ( li_Real_s(      6281881192751255665529323520.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 0] +
                   ( li_Real_s(    -40285977219890127336481226752.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 1] +
                   ( li_Real_s(    110615734080893297663288541184.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 2] +
                   ( li_Real_s(   -168654853846097186882804776960.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 3] +
                   ( li_Real_s(    154315777229842901771065753600.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 4] +
                   ( li_Real_s(    -84805396170918650104290213888.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 5] +
                   ( li_Real_s(     25946900602299293482203742208.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 6] +
                   ( li_Real_s(     -3414065868878242187627724800.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 7] +
                   ( li_Real_s(    -33156899297100925331906232320.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 8] +
                   ( li_Real_s(    212636636846112504141301415936.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 9] +
                   ( li_Real_s(   -583849748782798190779314470912.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[10] +
                   ( li_Real_s(    890190666590107080419476242432.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[11] +
                   ( li_Real_s(   -814506440070864708100784390144.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[12] +
                   ( li_Real_s(    447618141045806158009335808000.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[13] +
                   ( li_Real_s(   -136952410322259079122879774720.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[14] +
                   ( li_Real_s(     18020053990997125580399312896.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[15] +
                   ( li_Real_s(     76571389536950789568699826176.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[16] +
                   ( li_Real_s(   -491055650455873929687599153152.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[17] +
                   ( li_Real_s(   1348322294954972374730627088384.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[18] +
                   ( li_Real_s(  -2055775351666243372524542885888.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[19] +
                   ( li_Real_s(   1880992832471654500015460581376.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[20] +
                   ( li_Real_s(  -1033713760402609110598306234368.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[21] +
                   ( li_Real_s(    316273131256493930862436417536.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[22] +
                   ( li_Real_s(    -41614885695345437453473284096.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[23] +
                   ( li_Real_s(   -101081769896224666083873783808.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[24] +
                   ( li_Real_s(    648241785487484997452733349888.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[25] +
                   ( li_Real_s(  -1779918123663803984102039748608.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[26] +
                   ( li_Real_s(   2713825782304765269957054300160.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[27] +
                   ( li_Real_s(  -2483095655999732838502418612224.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[28] +
                   ( li_Real_s(   1364603896316398090776968429568.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[29] +
                   ( li_Real_s(   -417511659184169704093521018880.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[30] +
                   ( li_Real_s(     54935744635283204031004016640.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[31] +
                   ( li_Real_s(     82664879340041028424026816512.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[32] +
                   ( li_Real_s(   -530133465614488344954964803584.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[33] +
                   ( li_Real_s(   1455620702967993660671474532352.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[34] +
                   ( li_Real_s(  -2219372307482755553844529201152.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[35] +
                   ( li_Real_s(   2030680735662282713196958580736.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[36] +
                   ( li_Real_s(  -1115975873696098561863284948992.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[37] +
                   ( li_Real_s(    341441893802145064584751349760.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[38] +
                   ( li_Real_s(    -44926564979120226116757880832.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[39] +
                   ( li_Real_s(    -41783929598788271469041287168.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[40] +
                   ( li_Real_s(    267962157373782260082865602560.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[41] +
                   ( li_Real_s(   -735760500347562074403852255232.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[42] +
                   ( li_Real_s(   1121807677077327623569142710272.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[43] +
                   ( li_Real_s(  -1026431316358575203294287757312.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[44] +
                   ( li_Real_s(    564083051058087474561254686720.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[45] +
                   ( li_Real_s(   -172585796662522035184978624512.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[46] +
                   ( li_Real_s(     22708657458250164566245769216.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[47] +
                   ( li_Real_s(     12011580512552031064399282176.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[48] +
                   ( li_Real_s(    -77030788122101308066419965952.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[49] +
                   ( li_Real_s(    211508265829074626778136313856.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[50] +
                   ( li_Real_s(   -322484825252900199429459410944.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[51] +
                   ( li_Real_s(    295067087223987874785033977856.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[52] +
                   ( li_Real_s(   -162156337378747124644422090752.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[53] +
                   ( li_Real_s(     49613050096280255965440245760.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[54] +
                   ( li_Real_s(     -6528032908146215826336251904.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[55] +
                   ( li_Real_s(     -1507131789995410903722360832.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[56] +
                   ( li_Real_s(      9665301703839508554909220864.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[57] +
                   ( li_Real_s(    -26538625035718979207613644800.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[58] +
                   ( li_Real_s(     40463212271240032918903455744.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[59] +
                   ( li_Real_s(    -37023020154515858217932685312.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[60] +
                   ( li_Real_s(     20346279225885071154262048768.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[61] +
                   ( li_Real_s(     -6225109587609718262251651072.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[62] +
                   ( li_Real_s(       819093366876180521311797248.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[63];
        liVC[44] = ( li_Real_s(     -1818952156047425959851196416.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 0] +
                   ( li_Real_s(     11665019264064733913146195968.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 1] +
                   ( li_Real_s(    -32029374936854766423247945728.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 2] +
                   ( li_Real_s(     48834911182610202091642159104.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 3] +
                   ( li_Real_s(    -44682955182537616770484666368.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 4] +
                   ( li_Real_s(     24555854136432474862575943680.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 5] +
                   ( li_Real_s(     -7513063263457030576401285120.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 6] +
                   ( li_Real_s(       988560955789613718013214720.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 7] +
                   ( li_Real_s(     10816269080132001999513190400.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 8] +
                   ( li_Real_s(    -69365203905118768991045681152.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 9] +
                   ( li_Real_s(    190460390449942109137055776768.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[10] +
                   ( li_Real_s(   -290393311466172249272003592192.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[11] +
                   ( li_Real_s(    265704001668238348739531505664.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[12] +
                   ( li_Real_s(   -146019632812717608685732364288.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[13] +
                   ( li_Real_s(     44675894105386859083904057344.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[14] +
                   ( li_Real_s(     -5878407119690635936129875968.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[15] +
                   ( li_Real_s(    -27674057848334554762104012800.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[16] +
                   ( li_Real_s(    177474936272706937115681751040.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[17] +
                   ( li_Real_s(   -487304062515077775732286423040.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[18] +
                   ( li_Real_s(    742988293153604843027317129216.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[19] +
                   ( li_Real_s(   -679819248237085786340807671808.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[20] +
                   ( li_Real_s(    373599781664523649679401943040.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[21] +
                   ( li_Real_s(   -114305891354451883510309322752.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[22] +
                   ( li_Real_s(     15040248864114561727013584896.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[23] +
                   ( li_Real_s(     39594690774123810347703861248.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[24] +
                   ( li_Real_s(   -253922473564971965615001567232.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[25] +
                   ( li_Real_s(    697210859960770404263512768512.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[26] +
                   ( li_Real_s(  -1063031373399770888505386860544.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[27] +
                   ( li_Real_s(    972652188208304868467780091904.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[28] +
                   ( li_Real_s(   -534528326616821674469970935808.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[29] +
                   ( li_Real_s(    163543288374473445441093500928.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[30] +
                   ( li_Real_s(    -21518853736107502950475104256.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[31] +
                   ( li_Real_s(    -34300240755469205699983048704.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[32] +
                   ( li_Real_s(    219968935400408458635885150208.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[33] +
                   ( li_Real_s(   -603982500919745789516790628352.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[34] +
                   ( li_Real_s(    920886900021372811766868738048.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[35] +
                   ( li_Real_s(   -842592872461097784679531020288.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[36] +
                   ( li_Real_s(    463053251313230354270788780032.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[37] +
                   ( li_Real_s(   -141674907843607043867389460480.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[38] +
                   ( li_Real_s(     18641435244908335429593333760.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[39] +
                   ( li_Real_s(     18027115178223004985495388160.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[40] +
                   ( li_Real_s(   -115608673495638250790997458944.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[41] +
                   ( li_Real_s(    317433985039133739042371272704.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[42] +
                   ( li_Real_s(   -483988853996543898401374208000.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[43] +
                   ( li_Real_s(    442840004270911911360982941696.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[44] +
                   ( li_Real_s(   -243366055534687707352832933888.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[45] +
                   ( li_Real_s(     74459823773100535761772478464.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[46] +
                   ( li_Real_s(     -9797345234499487437533741056.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[47] +
                   ( li_Real_s(     -5326931333937411638163406848.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[48] +
                   ( li_Real_s(     34161842272576239505023959040.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[49] +
                   ( li_Real_s(    -93800312739012632860579332096.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[50] +
                   ( li_Real_s(    143016526294817667484372434944.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[51] +
                   ( li_Real_s(   -130857226552501796777731555328.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[52] +
                   ( li_Real_s(     71913573203518599259689582592.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[53] +
                   ( li_Real_s(    -22002542531520404725767864320.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[54] +
                   ( li_Real_s(      2895071386059792529714315264.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[55] +
                   ( li_Real_s(       682107061239491422926667776.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[56] +
                   ( li_Real_s(     -4374382243582413615954657280.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[57] +
                   ( li_Real_s(     12011015659646064095781715968.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[58] +
                   ( li_Real_s(    -18313091788125580550719143936.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[59] +
                   ( li_Real_s(     16756108284157911492452155392.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[60] +
                   ( li_Real_s(     -9208445352609904386535063552.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[61] +
                   ( li_Real_s(      2817398739814805096408023040.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[62] +
                   ( li_Real_s(      -370710360540521095076249600.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[63];
        liVC[45] = ( li_Real_s(       298827854720718447386296320.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 0] +
                   ( li_Real_s(     -1916396025388678869222948864.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 1] +
                   ( li_Real_s(      5261968749540699925917990912.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 2] +
                   ( li_Real_s(     -8022878281616496000654901248.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 3] +
                   ( li_Real_s(      7340771223801688354256322560.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 4] +
                   ( li_Real_s(     -4034176045407438187794530304.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 5] +
                   ( li_Real_s(      1234288967453440202405576704.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 6] +
                   ( li_Real_s(      -162406443104112611652796416.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 7] +
                   ( li_Real_s(     -1916396026990468849043767296.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 8] +
                   ( li_Real_s(     12289931047469972286712315904.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 9] +
                   ( li_Real_s(    -33745234416245887973151735808.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[10] +
                   ( li_Real_s(     51451067311494954168048680960.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[11] +
                   ( li_Real_s(    -47076685089285036688803889152.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[12] +
                   ( li_Real_s(     25871346416041680491505516544.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[13] +
                   ( li_Real_s(     -7915548824841094697796501504.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[14] +
                   ( li_Real_s(      1041519582355873153631125504.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[15] +
                   ( li_Real_s(      5261968756750769415291666432.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[16] +
                   ( li_Real_s(    -33745234434118062454557638656.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[17] +
                   ( li_Real_s(     92656406458152493430261940224.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[18] +
                   ( li_Real_s(   -141272422260602619603523207168.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[19] +
                   ( li_Real_s(    129261406659079458144724713472.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[20] +
                   ( li_Real_s(    -71036578375167675274853613568.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[21] +
                   ( li_Real_s(     21734218832128391406233321472.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[22] +
                   ( li_Real_s(     -2859765636222716580670210048.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[23] +
                   ( li_Real_s(     -8022878294937169531114618880.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[24] +
                   ( li_Real_s(     51451067353206722170707771392.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[25] +
                   ( li_Real_s(   -141272422299557349005394444288.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[26] +
                   ( li_Real_s(    215396841517709340489331769344.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[27] +
                   ( li_Real_s(   -197083749818751056726502408192.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[28] +
                   ( li_Real_s(    108308857241468565545562406912.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[29] +
                   ( li_Real_s(    -33137975654296491464058732544.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[30] +
                   ( li_Real_s(      4360259955157665020863578112.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[31] +
                   ( li_Real_s(      7340771237082901511906787328.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[32] +
                   ( li_Real_s(    -47076685133931955379857522688.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[33] +
                   ( li_Real_s(    129261406711388398380726091776.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[34] +
                   ( li_Real_s(   -197083749843385218922637688832.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[35] +
                   ( li_Real_s(    180327641641438218449508630528.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[36] +
                   ( li_Real_s(    -99100411948193652220331294720.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[37] +
                   ( li_Real_s(     30320576932563403576054906880.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[38] +
                   ( li_Real_s(     -3989549596962070656358285312.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[39] +
                   ( li_Real_s(     -4034176053053015986593071104.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[40] +
                   ( li_Real_s(     25871346442542668296069578752.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[41] +
                   ( li_Real_s(    -71036578408698373079417487360.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[42] +
                   ( li_Real_s(    108308857261809178815697518592.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[43] +
                   ( li_Real_s(    -99100411954321925413275697152.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[44] +
                   ( li_Real_s(     54461376855513593534000136192.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[45] +
                   ( li_Real_s(    -16662901135615163069208985600.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[46] +
                   ( li_Real_s(      2192486991823013812983824384.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[47] +
                   ( li_Real_s(      1234288969875250077390340096.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[48] +
                   ( li_Real_s(     -7915548833424914905634439168.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[49] +
                   ( li_Real_s(     21734218843565520154452295680.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[50] +
                   ( li_Real_s(    -33137975662233826322555076608.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[51] +
                   ( li_Real_s(     30320576936024028463549644800.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[52] +
                   ( li_Real_s(    -16662901136508991255800184832.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[53] +
                   ( li_Real_s(      5098150107450145353647521792.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[54] +
                   ( li_Real_s(      -670809224747214726146031616.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[55] +
                   ( li_Real_s(      -162406443434554132548026368.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[56] +
                   ( li_Real_s(      1041519583553214653122215936.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[57] +
                   ( li_Real_s(     -2859765637899947901563437056.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[58] +
                   ( li_Real_s(      4360259956456939769464619008.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[59] +
                   ( li_Real_s(     -3989549597654797066717626368.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[60] +
                   ( li_Real_s(      2192486992075333864494465024.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[61] +
                   ( li_Real_s(      -670809224788892813908508672.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[62] +
                   ( li_Real_s(        88264371692696652629409792.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[63];
        liVC[46] = ( li_Real_s(       -25985030916514745344327680.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 0] +
                   ( li_Real_s(       166643133110385871301902336.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 1] +
                   ( li_Real_s(      -457562501284252009233383424.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 2] +
                   ( li_Real_s(       697641591791951230686724096.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 3] +
                   ( li_Real_s(      -638327934474639604738686976.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 4] +
                   ( li_Real_s(       350797918105127388526411776.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 5] +
                   ( li_Real_s(      -107329475778859587231285248.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 6] +
                   ( li_Real_s(        14122299446829993942843392.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 7] +
                   ( li_Real_s(       175398958881541601229799424.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 8] +
                   ( li_Real_s(     -1124841149867511720773156864.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 9] +
                   ( li_Real_s(      3088546887675055730084282368.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[10] +
                   ( li_Real_s(     -4709080750962772253643636736.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[11] +
                   ( li_Real_s(      4308713563701863852340674560.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[12] +
                   ( li_Real_s(     -2367885950576034840072683520.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[13] +
                   ( li_Real_s(       724473962553493196996870144.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[14] +
                   ( li_Real_s(       -95325521405636493875085312.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[15] +
                   ( li_Real_s(      -506708103817662730042605568.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[16] +
                   ( li_Real_s(      3249541102276209327562817536.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[17] +
                   ( li_Real_s(     -8922468794281860161144356864.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[18] +
                   ( li_Real_s(     13604011070373846735363506176.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[19] +
                   ( li_Real_s(    -12447394750797279366043664384.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[20] +
                   ( li_Real_s(      6840559419003572030615322624.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[21] +
                   ( li_Real_s(     -2092924782626476331362156544.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[22] +
                   ( li_Real_s(       275384839869650632490090496.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[23] +
                   ( li_Real_s(       812032218024351489423572992.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[24] +
                   ( li_Real_s(     -5207597922844101885235822592.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[25] +
                   ( li_Real_s(     14298828203126056380077703168.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[26] +
                   ( li_Real_s(    -21801299803284768955228487680.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[27] +
                   ( li_Real_s(     19947748008125230717211770880.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[28] +
                   ( li_Real_s(    -10962434971819514156766199808.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[29] +
                   ( li_Real_s(      3354046127652159390281105408.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[30] +
                   ( li_Real_s(      -441321858979437787494744064.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[31] +
                   ( li_Real_s(      -779550929499240368523182080.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[32] +
                   ( li_Real_s(      4999294007249975711685935104.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[33] +
                   ( li_Real_s(    -13726875078607004037302714368.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[34] +
                   ( li_Real_s(     20929247816464717768963391488.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[35] +
                   ( li_Real_s(    -19149838092415735126829301760.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[36] +
                   ( li_Real_s(     10523937575329160135450820608.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[37] +
                   ( li_Real_s(     -3219884283225875017688416256.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[38] +
                   ( li_Real_s(       423668984704006156923699200.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[39] +
                   ( li_Real_s(       448241784515906588370796544.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[40] +
                   ( li_Real_s(     -2874594054519099482603257856.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[41] +
                   ( li_Real_s(      7892953171083844075665752064.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[42] +
                   ( li_Real_s(    -12034317495627685007913385984.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[43] +
                   ( li_Real_s(     11011156904000059585597538304.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[44] +
                   ( li_Real_s(     -6051264106171884224378830848.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[45] +
                   ( li_Real_s(      1851433462929430301189865472.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[46] +
                   ( li_Real_s(      -243609666210573931872518144.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[47] +
                   ( li_Real_s(      -142917670429532696313069568.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[48] +
                   ( li_Real_s(       916537234797886128777068544.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[49] +
                   ( li_Real_s(     -2516593764725588671552552960.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[50] +
                   ( li_Real_s(      3837028766702779961027067904.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[51] +
                   ( li_Real_s(     -3510803650464462926849769472.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[52] +
                   ( li_Real_s(      1929388555505149230704492544.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[53] +
                   ( li_Real_s(      -590312118577534771000246272.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[54] +
                   ( li_Real_s(        77672647191303521868709888.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[55] +
                   ( li_Real_s(        19488773239692419154313216.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[56] +
                   ( li_Real_s(      -124982350194422273955332096.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[57] +
                   ( li_Real_s(       343171876988569189934432256.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[58] +
                   ( li_Real_s(      -523231195420328605192814592.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[59] +
                   ( li_Real_s(       478745952290990159036416000.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[60] +
                   ( li_Real_s(      -263098439357204511485591552.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[61] +
                   ( li_Real_s(        80497107068131914549297152.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[62] +
                   ( li_Real_s(       -10591724615427149579419648.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[63];
        liVC[47] = ( li_Real_s(          928036821681332159512576.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 0] +
                   ( li_Real_s(        -5951540489259187326418944.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 1] +
                   ( li_Real_s(        16341517961955771064254464.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 2] +
                   ( li_Real_s(       -24915771227473567186681856.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 3] +
                   ( li_Real_s(        22797426317520187038892032.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 4] +
                   ( li_Real_s(       -12528497123659033295716352.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 5] +
                   ( li_Real_s(         3833195578633204562657280.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 6] +
                   ( li_Real_s(         -504367839399056855007232.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 7] +
                   ( li_Real_s(        -6496257757360206452359168.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 8] +
                   ( li_Real_s(        41660783465367103657213952.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 9] +
                   ( li_Real_s(      -114390625853358210770010112.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[10] +
                   ( li_Real_s(       174410398782727655270645760.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[11] +
                   ( li_Real_s(      -159581984401454799398109184.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[12] +
                   ( li_Real_s(        87699479965540659438288896.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[13] +
                   ( li_Real_s(       -26832369081382938009927680.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[14] +
                   ( li_Real_s(         3530574879920757739094016.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[15] +
                   ( li_Real_s(        19488773280152428421840896.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[16] +
                   ( li_Real_s(      -124982350454437858888384512.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[17] +
                   ( li_Real_s(       343171877728633836477087744.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[18] +
                   ( li_Real_s(      -523231196608909608350646272.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[19] +
                   ( li_Real_s(       478745953441758338839740416.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[20] +
                   ( li_Real_s(      -263098440025245683210518528.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[21] +
                   ( li_Real_s(        80497107282861707910709248.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[22] +
                   ( li_Real_s(       -10591724644813154757378048.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[23] +
                   ( li_Real_s(       -32481288802417350813941760.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[24] +
                   ( li_Real_s(       208303917440542750223106048.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[25] +
                   ( li_Real_s(      -571953129588594450620219392.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[26] +
                   ( li_Real_s(       872051994394156468650639360.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[27] +
                   ( li_Real_s(      -797909922426212013349797888.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[28] +
                   ( li_Real_s(       438497400044177019073724416.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[29] +
                   ( li_Real_s(      -134161845469070924181405696.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[30] +
                   ( li_Real_s(        17652874407419235457302528.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[31] +
                   ( li_Real_s(        32481288797533474782183424.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[32] +
                   ( li_Real_s(      -208303917406871512292524032.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[33] +
                   ( li_Real_s(       571953129481130589303078912.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[34] +
                   ( li_Real_s(      -872051994201102705217241088.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[35] +
                   ( li_Real_s(       797909922221313486028275712.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[36] +
                   ( li_Real_s(      -438497399916674901937750016.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[37] +
                   ( li_Real_s(       134161845426017261473234944.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[38] +
                   ( li_Real_s(       -17652874401345644894617600.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[39] +
                   ( li_Real_s(       -19488773273075404649791488.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[40] +
                   ( li_Real_s(       124982350406313557790556160.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[41] +
                   ( li_Real_s(      -343171877573005662146789376.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[42] +
                   ( li_Real_s(       523231196323667910961659904.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[43] +
                   ( li_Real_s(      -478745953133518637768900608.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[44] +
                   ( li_Real_s(       263098439830740323910287360.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[45] +
                   ( li_Real_s(       -80497107216523154885181440.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[46] +
                   ( li_Real_s(        10591724635400933644173312.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[47] +
                   ( li_Real_s(         6496257755365908181680128.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[48] +
                   ( li_Real_s(       -41660783452697843487211520.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[49] +
                   ( li_Real_s(       114390625809351752516894720.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[50] +
                   ( li_Real_s(      -174410398693934944502153216.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[51] +
                   ( li_Real_s(       159581984297807961416269824.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[52] +
                   ( li_Real_s(       -87699479896440236283002880.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[53] +
                   ( li_Real_s(        26832369056924894555537408.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[54] +
                   ( li_Real_s(        -3530574876377418846699520.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[55] +
                   ( li_Real_s(         -928036821820777131147264.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[56] +
                   ( li_Real_s(         5951540490665222180175872.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[57] +
                   ( li_Real_s(       -16341517965092774375063552.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[58] +
                   ( li_Real_s(        24915771229336895798378496.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[59] +
                   ( li_Real_s(       -22797426315834652893380608.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[60] +
                   ( li_Real_s(        12528497120815563082301440.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[61] +
                   ( li_Real_s(        -3833195577235325314924544.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[62] +
                   ( li_Real_s(          504367839165680076193792.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[63];
        liVC[48] = ( li_Real_s(       406722222218871368618868736.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 0] +
                   ( li_Real_s(     -2745374999935287296285212672.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 1] +
                   ( li_Real_s(      7931083333070765999561637888.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 2] +
                   ( li_Real_s(    -12710069443915197061644943360.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 3] +
                   ( li_Real_s(     12201666666047055159462199296.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 4] +
                   ( li_Real_s(     -7015958332911061884743974912.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 5] +
                   ( li_Real_s(      2236972222068405434427899904.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 6] +
                   ( li_Real_s(      -305041666643547768026562560.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 7] +
                   ( li_Real_s(              -2294500704426015488.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 8] +
                   ( li_Real_s(              15285797723435929600.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 9] +
                   ( li_Real_s(             -43781861737250422784.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[10] +
                   ( li_Real_s(              69554052813679124480.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[11] +
                   ( li_Real_s(             -66090222713867182080.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[12] +
                   ( li_Real_s(              37582020142641987584.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[13] +
                   ( li_Real_s(             -11858212520336363520.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[14] +
                   ( li_Real_s(               1602926996122932480.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[15] +
                   ( li_Real_s(               6093338310926864384.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[16] +
                   ( li_Real_s(             -40745925669727641600.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[17] +
                   ( li_Real_s(             116948598308930633728.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[18] +
                   ( li_Real_s(            -185956652251016724480.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[19] +
                   ( li_Real_s(             176716420388801740800.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[20] +
                   ( li_Real_s(            -100455768582961872896.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[21] +
                   ( li_Real_s(              31679787295210082304.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[22] +
                   ( li_Real_s(              -4279797800163090944.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[23] +
                   ( li_Real_s(              -8977175898010437632.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[24] +
                   ( li_Real_s(              60267105414081806336.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[25] +
                   ( li_Real_s(            -173373649013275852800.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[26] +
                   ( li_Real_s(             275968735800928501760.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[27] +
                   ( li_Real_s(            -262317000235060559872.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[28] +
                   ( li_Real_s(             149077685574721798144.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[29] +
                   ( li_Real_s(             -46990261868780019712.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[30] +
                   ( li_Real_s(               6344560225394571264.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[31] +
                   ( li_Real_s(               7917121563479038976.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[32] +
                   ( li_Real_s(             -53375427277812367360.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[33] +
                   ( li_Real_s(             153944359313378246656.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[34] +
                   ( li_Real_s(            -245365774346543464448.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[35] +
                   ( li_Real_s(             233332100959790530560.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[36] +
                   ( li_Real_s(            -132593412795415937024.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[37] +
                   ( li_Real_s(              41779360908048031744.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[38] +
                   ( li_Real_s(              -5638328324924065792.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[39] +
                   ( li_Real_s(              -4183154435839277568.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[40] +
                   ( li_Real_s(              28328647263704051712.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[41] +
                   ( li_Real_s(             -81939617711146876928.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[42] +
                   ( li_Real_s(             130808188881314906112.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[43] +
                   ( li_Real_s(            -124477456180876656640.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[44] +
                   ( li_Real_s(              70743099938085994496.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[45] +
                   ( li_Real_s(             -22286320043265662976.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[46] +
                   ( li_Real_s(               3006612288023531520.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[47] +
                   ( li_Real_s(               1228750379247239680.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[48] +
                   ( li_Real_s(              -8359679549982935040.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[49] +
                   ( li_Real_s(              24254017377933737984.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[50] +
                   ( li_Real_s(             -38788250332826370048.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[51] +
                   ( li_Real_s(              36942898649847291904.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[52] +
                   ( li_Real_s(             -21001073736778235904.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[53] +
                   ( li_Real_s(               6615641950154079232.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[54] +
                   ( li_Real_s(               -892304737594812800.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[55] +
                   ( li_Real_s(               -155289086479418432.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[56] +
                   ( li_Real_s(               1061293352892852480.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[57] +
                   ( li_Real_s(              -3088566363033888256.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[58] +
                   ( li_Real_s(               4948497605194021888.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[59] +
                   ( li_Real_s(              -4717536263174434816.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[60] +
                   ( li_Real_s(               2682763396062942720.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[61] +
                   ( li_Real_s(               -845137398372021248.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[62] +
                   ( li_Real_s(                113974756910043808.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[63];
        liVC[49] = ( li_Real_s(     -1054572617585264710559727616.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 0] +
                   ( li_Real_s(      7118365169270078631145635840.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 1] +
                   ( li_Real_s(    -20564166046388696192714276864.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 2] +
                   ( li_Real_s(     32955394307905885366774661120.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 3] +
                   ( li_Real_s(    -31637178537905798463902187520.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 4] +
                   ( li_Real_s(     18191377660358133872989306880.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 5] +
                   ( li_Real_s(     -5800149399203389910932258816.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 6] +
                   ( li_Real_s(       790929463549150500684300288.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 7] +
                   ( li_Real_s(      2847055551205342173357670400.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 8] +
                   ( li_Real_s(    -19217624974573349374017929216.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 9] +
                   ( li_Real_s(     55517583271667105830151389184.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[10] +
                   ( li_Real_s(    -88970486029537114374837108736.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[11] +
                   ( li_Real_s(     85411666602148516570427555840.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[12] +
                   ( li_Real_s(    -49111708302321886580061503488.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[13] +
                   ( li_Real_s(     15658805547021852324883595264.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[14] +
                   ( li_Real_s(     -2135291665610480863554830336.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[15] +
                   ( li_Real_s(     -4270583327842241110035398656.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[16] +
                   ( li_Real_s(     28826437474320119736030986240.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[17] +
                   ( li_Real_s(    -83276374958083590025992208384.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[18] +
                   ( li_Real_s(    133455729145044211128674025472.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[19] +
                   ( li_Real_s(   -128117500014495911249641996288.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[20] +
                   ( li_Real_s(     73667562523290343730520784896.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[21] +
                   ( li_Real_s(    -23488208343895303808891224064.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[22] +
                   ( li_Real_s(      3202937501662362803242008576.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[23] +
                   ( li_Real_s(      4745092589501611011643277312.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[24] +
                   ( li_Real_s(    -32029374997263852801540227072.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[25] +
                   ( li_Real_s(     92529305596792598431608602624.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[26] +
                   ( li_Real_s(   -148284143651856397277052534784.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[27] +
                   ( li_Real_s(    142352777956313654401286799360.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[28] +
                   ( li_Real_s(    -81852847345502006320004333568.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[29] +
                   ( li_Real_s(     26098009302616143177109733376.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[30] +
                   ( li_Real_s(     -3558819450601714888923414528.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[31] +
                   ( li_Real_s(     -3558819444838738491388985344.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[32] +
                   ( li_Real_s(     24022031269879838144798392320.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[33] +
                   ( li_Real_s(    -69396979269063140035751051264.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[34] +
                   ( li_Real_s(    111213107862876971843392110592.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[35] +
                   ( li_Real_s(   -106764583592154464385805320192.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[36] +
                   ( li_Real_s(     61389635582687597366031155200.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[37] +
                   ( li_Real_s(    -19573507000518497495095967744.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[38] +
                   ( li_Real_s(      2669114591130458342587105280.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[39] +
                   ( li_Real_s(      1708233334820050775171923968.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[40] +
                   ( li_Real_s(    -11530575019808918015666290688.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[41] +
                   ( li_Real_s(     33310550081951568425000108032.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[42] +
                   ( li_Real_s(    -53382291830146646714611662848.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[43] +
                   ( li_Real_s(     51247000179857789465615400960.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[44] +
                   ( li_Real_s(    -29467025112079288742906429440.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[45] +
                   ( li_Real_s(      9395283370524260129480638464.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[46] +
                   ( li_Real_s(     -1281175005118876619856936960.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[47] +
                   ( li_Real_s(      -474509259998376374592077824.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[48] +
                   ( li_Real_s(      3202937508063300586223697920.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[49] +
                   ( li_Real_s(     -9252930586419815398449872896.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[50] +
                   ( li_Real_s(     14828414410947961947798110208.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[51] +
                   ( li_Real_s(    -14235277841218483121163337728.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[52] +
                   ( li_Real_s(      8185284761141432172828164096.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[53] +
                   ( li_Real_s(     -2609800938708589198404747264.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[54] +
                   ( li_Real_s(       355881946192582030143782912.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[55] +
                   ( li_Real_s(        58103174726635723388092416.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[56] +
                   ( li_Real_s(      -392196429818579137696104448.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[57] +
                   ( li_Real_s(      1133011909360307918233141248.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[58] +
                   ( li_Real_s(     -1815724214962164174268923904.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[59] +
                   ( li_Real_s(      1743095247211635444212039680.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[60] +
                   ( li_Real_s(     -1002279767444162976438812672.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[61] +
                   ( li_Real_s(       319567462124726040162992128.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[62] +
                   ( li_Real_s(       -43577381198432355517202432.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[63];
        liVC[50] = ( li_Real_s(      1059737342526029140865318912.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 0] +
                   ( li_Real_s(     -7153227063564411916626427904.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 1] +
                   ( li_Real_s(     20664878188214130249511731200.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 2] +
                   ( li_Real_s(    -33116791975206457341640704000.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 3] +
                   ( li_Real_s(     31792120301953856546359214080.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 4] +
                   ( li_Real_s(    -18280469176287210904060166144.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 5] +
                   ( li_Real_s(      5828555390168555751362002944.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 6] +
                   ( li_Real_s(      -794803007804770114529656832.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 7] +
                   ( li_Real_s(     -4534952763131531375205679104.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 8] +
                   ( li_Real_s(     30610931161328324128999997440.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 9] +
                   ( li_Real_s(    -88431578939791922453456879616.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[10] +
                   ( li_Real_s(    141717273984646924443074953216.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[11] +
                   ( li_Real_s(   -136048583059760011097394905088.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[12] +
                   ( li_Real_s(     78227935274828201371010859008.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[13] +
                   ( li_Real_s(    -24942240236046721293320454144.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[14] +
                   ( li_Real_s(      3401214577926741773850247168.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[15] +
                   ( li_Real_s(      8937720804027219074437087232.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[16] +
                   ( li_Real_s(    -60329615456096631651982901248.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[17] +
                   ( li_Real_s(    174285555841768463947519754240.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[18] +
                   ( li_Real_s(   -279303775500312550979366027264.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[19] +
                   ( li_Real_s(    268131624569215674729279520768.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[20] +
                   ( li_Real_s(   -154175684165934855851654250496.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[21] +
                   ( li_Real_s(     49157464524999025326175551488.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[22] +
                   ( li_Real_s(     -6703290617666374281222684672.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[23] +
                   ( li_Real_s(    -10721649658165617198215725056.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[24] +
                   ( li_Real_s(     72371135237862917427473416192.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[25] +
                   ( li_Real_s(   -209072168585486038074392576000.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[26] +
                   ( li_Real_s(    335051552386936730489941131264.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[27] +
                   ( li_Real_s(   -321649490419753939988694171648.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[28] +
                   ( li_Real_s(    184948457045469641489137008640.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[29] +
                   ( li_Real_s(    -58969073271964761127747846144.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[30] +
                   ( li_Real_s(      8041237265101291282870829056.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[31] +
                   ( li_Real_s(      8337805532667414256388407296.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[32] +
                   ( li_Real_s(    -56280187387770763859395084288.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[33] +
                   ( li_Real_s(    162587208118493615853894893568.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[34] +
                   ( li_Real_s(   -260556423414819854758602342400.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[35] +
                   ( li_Real_s(    250134166589855567916449136640.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[36] +
                   ( li_Real_s(   -143827145834901713853393928192.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[37] +
                   ( li_Real_s(     45857930564937400920615944192.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[38] +
                   ( li_Real_s(     -6253354168461693963747721216.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[39] +
                   ( li_Real_s(     -4087558323822116746332995584.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[40] +
                   ( li_Real_s(     27591018709420349362372870144.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[41] +
                   ( li_Real_s(    -79707387442351655301586878464.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[42] +
                   ( li_Real_s(    127736197903378559251853082624.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[43] +
                   ( li_Real_s(   -122626750045751272789317255168.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[44] +
                   ( li_Real_s(     70510381299593572043678810112.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[45] +
                   ( li_Real_s(    -22481570853407581376016809984.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[46] +
                   ( li_Real_s(      3065668752940165896314290176.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[47] +
                   ( li_Real_s(      1151249843478174494697193472.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[48] +
                   ( li_Real_s(     -7770936450806099619186999296.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[49] +
                   ( li_Real_s(     22449371987066605754459881472.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[50] +
                   ( li_Real_s(    -35976557695159372516708843520.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[51] +
                   ( li_Real_s(     34537495404478468242353946624.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[52] +
                   ( li_Real_s(    -19859059864198518131350568960.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[53] +
                   ( li_Real_s(      6331874160735698076643098624.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[54] +
                   ( li_Real_s(      -863437385594938708721664000.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[55] +
                   ( li_Real_s(      -142352777556081611498323968.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[56] +
                   ( li_Real_s(       960881249477646763107024896.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[57] +
                   ( li_Real_s(     -2775879167513548389974278144.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[58] +
                   ( li_Real_s(      4448524309939907438554644480.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[59] +
                   ( li_Real_s(     -4270583339704875910401359872.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[60] +
                   ( li_Real_s(      2455585421143998163201294336.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[61] +
                   ( li_Real_s(      -782940279335634880736264192.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[62] +
                   ( li_Real_s(       106764583548554325706932224.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[63];
        liVC[51] = ( li_Real_s(      -546250538117414533581504512.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 0] +
                   ( li_Real_s(      3687191133491013439488786432.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 1] +
                   ( li_Real_s(    -10651885500338818257447288832.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 2] +
                   ( li_Real_s(     17070329332832203525003935744.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 3] +
                   ( li_Real_s(    -16387516163943130007966056448.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 4] +
                   ( li_Real_s(      9422821796281180260348723200.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 5] +
                   ( li_Real_s(     -3004377964492159183975612416.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 6] +
                   ( li_Real_s(       409687904286633207711924224.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 7] +
                   ( li_Real_s(      2883208632515313722678312960.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 8] +
                   ( li_Real_s(    -19461658277657350265909542912.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 9] +
                   ( li_Real_s(     56222568380769397457318576128.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[10] +
                   ( li_Real_s(    -90100269874270993878402203648.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[11] +
                   ( li_Real_s(     86496259105901828517671206912.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[12] +
                   ( li_Real_s(    -49735348997582956051998703616.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[13] +
                   ( li_Real_s(     15857647509016453800513241088.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[14] +
                   ( li_Real_s(     -2162406478691687804312748032.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[15] +
                   ( li_Real_s(     -6658381694322363918469562368.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[16] +
                   ( li_Real_s(     44944076460020037188801527808.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[17] +
                   ( li_Real_s(   -129838443169901315243678629888.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[18] +
                   ( li_Real_s(    208074428245304258041166692352.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[19] +
                   ( li_Real_s(   -199751451184214676161387560960.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[20] +
                   ( li_Real_s(    114857084460089946248300199936.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[21] +
                   ( li_Real_s(    -36621099399060685864262696960.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[22] +
                   ( li_Real_s(      4993786282084849187553280000.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[23] +
                   ( li_Real_s(      8789719115687816296736489472.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[24] +
                   ( li_Real_s(    -59330604067525970933229551616.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[25] +
                   ( li_Real_s(    171399522957541344422796460032.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[26] +
                   ( li_Real_s(   -274678722819136911913301049344.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[27] +
                   ( li_Real_s(    263691574005592866396275998720.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[28] +
                   ( li_Real_s(   -151622655093941804472635228160.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[29] +
                   ( li_Real_s(     48343455255202902292524171264.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[30] +
                   ( li_Real_s(     -6592289353419888046423146496.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[31] +
                   ( li_Real_s(     -7188250373069116216270913536.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[32] +
                   ( li_Real_s(     48520690052470210637678510080.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[33] +
                   ( li_Real_s(   -140170882460787736697970360320.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[34] +
                   ( li_Real_s(    224632824572573313679199567872.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[35] +
                   ( li_Real_s(   -215647511675897490236818587648.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[36] +
                   ( li_Real_s(    123997319247879829623710679040.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[37] +
                   ( li_Real_s(    -39535377157661868112656465920.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[38] +
                   ( li_Real_s(      5391187794492882611895009280.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[39] +
                   ( li_Real_s(      3633385180555507155974750208.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[40] +
                   ( li_Real_s(    -24525349987891754027502796800.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[41] +
                   ( li_Real_s(     70851011123499879322347372544.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[42] +
                   ( li_Real_s(   -113543287118920706235199127552.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[43] +
                   ( li_Real_s(    109001555679245664608707411968.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[44] +
                   ( li_Real_s(    -62675894532873386448633462784.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[45] +
                   ( li_Real_s(     19983618549589927657312616448.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[46] +
                   ( li_Real_s(     -2725038893205162819332341760.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[47] +
                   ( li_Real_s(     -1044485261478489056438386688.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[48] +
                   ( li_Real_s(      7050275520918649051920990208.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[49] +
                   ( li_Real_s(    -20367462630346800666324762624.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[50] +
                   ( li_Real_s(     32640164490176739551284822016.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[51] +
                   ( li_Real_s(    -31334557923727042537400041472.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[52] +
                   ( li_Real_s(     18017370811025285266804834304.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[53] +
                   ( li_Real_s(     -5744668954980627366207815680.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[54] +
                   ( li_Real_s(       783363948412303485985357824.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[55] +
                   ( li_Real_s(       131054938209694194704842752.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[56] +
                   ( li_Real_s(      -884620833704717981398859776.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[57] +
                   ( li_Real_s(      2555571299240310558787895296.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[58] +
                   ( li_Real_s(     -4095466828073635517682417664.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[59] +
                   ( li_Real_s(      3931648156607168751620587520.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[60] +
                   ( li_Real_s(     -2260697690643726650488913920.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[61] +
                   ( li_Real_s(       720802162315675937946992640.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[62] +
                   ( li_Real_s(       -98291203950697515996676096.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[63];
        liVC[52] = ( li_Real_s(       158169752618974515956809728.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 0] +
                   ( li_Real_s(     -1067645830590916509852237824.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 1] +
                   ( li_Real_s(      3084310178503679999500877824.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 2] +
                   ( li_Real_s(     -4942804775095082291004702720.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 3] +
                   ( li_Real_s(      4745092585598886242515156992.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 4] +
                   ( li_Real_s(     -2728428237386973813934129152.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 5] +
                   ( li_Real_s(       869933641050488208088891392.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 6] +
                   ( li_Real_s(      -118627314699006512470163456.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 7] +
                   ( li_Real_s(      -940545137051419010454781952.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 8] +
                   ( li_Real_s(      6348679677982550668439715840.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 9] +
                   ( li_Real_s(    -18340630188944567611953250304.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[10] +
                   ( li_Real_s(     29392035570784355496247689216.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[11] +
                   ( li_Real_s(    -28216354157030655532120145920.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[12] +
                   ( li_Real_s(     16224403644137564117720367104.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[13] +
                   ( li_Real_s(     -5172998264123290990975909888.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[14] +
                   ( li_Real_s(       705408854245461351267827712.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[15] +
                   ( li_Real_s(      2406439812307298111706890240.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[16] +
                   ( li_Real_s(    -16243468741439150317876805632.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[17] +
                   ( li_Real_s(     46925576386532065050932281344.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[18] +
                   ( li_Real_s(    -75201244240056425354054598656.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[19] +
                   ( li_Real_s(     72193194493874181890799304704.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[20] +
                   ( li_Real_s(    -41511086843463375815912194048.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[21] +
                   ( li_Real_s(     13235418995324722532799479808.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[22] +
                   ( li_Real_s(     -1804829863079326818632728576.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[23] +
                   ( li_Real_s(     -3443016588606835385020973056.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[24] +
                   ( li_Real_s(     23240361986339718059985469440.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[25] +
                   ( li_Real_s(    -67138823550173400534936977408.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[26] +
                   ( li_Real_s(    107594268555588006219259838464.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[27] +
                   ( li_Real_s(   -103290497847034595868112060416.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[28] +
                   ( li_Real_s(     59392036275089530242033778688.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[29] +
                   ( li_Real_s(    -18936591278301703784357691392.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[30] +
                   ( li_Real_s(      2582262447099266207741640704.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[31] +
                   ( li_Real_s(      2982629630847281687544463360.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[32] +
                   ( li_Real_s(    -20132750020660882335527337984.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[33] +
                   ( li_Real_s(     58161277868450703576173379584.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[34] +
                   ( li_Real_s(    -93207176111750559398704971776.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[35] +
                   ( li_Real_s(     89478889096333248367299657728.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[36] +
                   ( li_Real_s(    -51450361241141563226977206272.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[37] +
                   ( li_Real_s(     16404463006013818781797711872.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[38] +
                   ( li_Real_s(     -2236972228092059546233602048.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[39] +
                   ( li_Real_s(     -1567575233018699399045316608.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[40] +
                   ( li_Real_s(     10581132829848566260838694912.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[41] +
                   ( li_Real_s(    -30567717080875474281178333184.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[42] +
                   ( li_Real_s(     48986726112700577575419772928.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[43] +
                   ( li_Real_s(    -47027257083245894632946532352.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[44] +
                   ( li_Real_s(     27040672828170107611089207296.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[45] +
                   ( li_Real_s(     -8621663800954374763787059200.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[46] +
                   ( li_Real_s(      1175681427375175274374103040.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[47] +
                   ( li_Real_s(       463211420425743635562102784.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[48] +
                   ( li_Real_s(     -3126677090041570221600276480.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[49] +
                   ( li_Real_s(      9032622709675140641923792896.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[50] +
                   ( li_Real_s(    -14475356912923379295315820544.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[51] +
                   ( li_Real_s(     13896342640758530784683360256.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[52] +
                   ( li_Real_s(     -7990397019892584850995019776.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[53] +
                   ( li_Real_s(      2547662818084520062768644096.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[54] +
                   ( li_Real_s(      -347408566086399588795678720.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[55] +
                   ( li_Real_s(       -59313657514837807546236928.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[56] +
                   ( li_Real_s(       400367188514439343019917312.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[57] +
                   ( li_Real_s(     -1156616323040543843133947904.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[58] +
                   ( li_Real_s(      1853551800561250299036041216.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[59] +
                   ( li_Real_s(     -1779409729081669188935745536.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[60] +
                   ( li_Real_s(      1023160594394379720163590144.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[61] +
                   ( li_Real_s(      -326225117066213418325770240.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[62] +
                   ( li_Real_s(        44485243233275555207970816.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[63];
        liVC[53] = ( li_Real_s(       -25985030845956077712834560.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 0] +
                   ( li_Real_s(       175398958275746222294695936.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 1] +
                   ( li_Real_s(      -506708101888998938400260096.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 2] +
                   ( li_Real_s(       812032214871250246052085760.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 3] +
                   ( li_Real_s(      -779550926521161172767473664.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 4] +
                   ( li_Real_s(       448241782853248538189496320.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 5] +
                   ( li_Real_s(      -142917669915429646467334144.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 6] +
                   ( li_Real_s(        19488773171290194472599552.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 7] +
                   ( li_Real_s(       166643132818957462501588992.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 8] +
                   ( li_Real_s(     -1124841147007799899549859840.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 9] +
                   ( li_Real_s(      3249541092715788598283075584.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[10] +
                   ( li_Real_s(     -5207597906921981644434833408.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[11] +
                   ( li_Real_s(      4999293992115733617512022016.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[12] +
                   ( li_Real_s(     -2874594046050691711798083584.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[13] +
                   ( li_Real_s(       916537232174616174208745472.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[14] +
                   ( li_Real_s(      -124982349844622923140169728.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[15] +
                   ( li_Real_s(      -457562500762998354235883520.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[16] +
                   ( li_Real_s(      3088546881577412182310649856.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[17] +
                   ( li_Real_s(     -8922468772802338662098403328.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[18] +
                   ( li_Real_s(     14298828166701760630556196864.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[19] +
                   ( li_Real_s(    -13726875043800087693216448512.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[20] +
                   ( li_Real_s(      7892953151583763464500281344.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[21] +
                   ( li_Real_s(     -2516593758678482526482202624.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[22] +
                   ( li_Real_s(       343171876180970752507379712.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[23] +
                   ( li_Real_s(       697641591222952588923109376.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[24] +
                   ( li_Real_s(     -4709080743046186279075053568.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[25] +
                   ( li_Real_s(     13604011041286840567619125248.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[26] +
                   ( li_Real_s(    -21801299753273324236162727936.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[27] +
                   ( li_Real_s(     20929247768489612565003894784.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[28] +
                   ( li_Real_s(    -12034317468729738321350098944.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[29] +
                   ( li_Real_s(      3837028758353714831568142336.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[30] +
                   ( li_Real_s(      -523231194303846015442092032.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[31] +
                   ( li_Real_s(      -638327934057502485346516992.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[32] +
                   ( li_Real_s(      4308713557056064280097456128.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[33] +
                   ( li_Real_s(    -12447394725676688827733770240.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[34] +
                   ( li_Real_s(     19947747964528288456079572992.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[35] +
                   ( li_Real_s(    -19149838050478914686150508544.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[36] +
                   ( li_Real_s(     11011156880469272701098262528.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[37] +
                   ( li_Real_s(     -3510803643152379099383595008.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[38] +
                   ( li_Real_s(       478745951311859523900145664.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[39] +
                   ( li_Real_s(       350797917909076837432033280.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[40] +
                   ( li_Real_s(     -2367885947105861518724431872.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[41] +
                   ( li_Real_s(      6840559405624632080464871424.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[42] +
                   ( li_Real_s(    -10962434948450087200712818688.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[43] +
                   ( li_Real_s(     10523937552809207066924154880.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[44] +
                   ( li_Real_s(     -6051264093530219597210320896.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[45] +
                   ( li_Real_s(      1929388551573376738760065024.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[46] +
                   ( li_Real_s(      -263098438830129251656663040.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[47] +
                   ( li_Real_s(      -107329475727440702620041216.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[48] +
                   ( li_Real_s(       724473961540496779091378176.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[49] +
                   ( li_Real_s(     -2092924778652076873120481280.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[50] +
                   ( li_Real_s(      3354046120674398016158826496.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[51] +
                   ( li_Real_s(     -3219884276496230537001697280.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[52] +
                   ( li_Real_s(      1851433459153207368494350336.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[53] +
                   ( li_Real_s(      -590312117402956598177955840.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[54] +
                   ( li_Real_s(        80497106910602976672350208.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[55] +
                   ( li_Real_s(        14122299441387827997179904.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[56] +
                   ( li_Real_s(       -95325521280168713768665088.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[57] +
                   ( li_Real_s(       275384839366603481299288064.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[58] +
                   ( li_Real_s(      -441321858090934879314247680.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[59] +
                   ( li_Real_s(       423668983846367502207549440.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[60] +
                   ( li_Real_s(      -243609665729654349111492608.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[61] +
                   ( li_Real_s(        77672647041761694153965568.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[62] +
                   ( li_Real_s(       -10591724595376530697224192.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[63];
        liVC[54] = ( li_Real_s(         2259567907736927407702016.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 0] +
                   ( li_Real_s(       -15252083381529592731795456.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 1] +
                   ( li_Real_s(        44061574227945274413678592.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 2] +
                   ( li_Real_s(       -70611497182639892209860608.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 3] +
                   ( li_Real_s(        67787037312895128961024000.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 4] +
                   ( li_Real_s(       -38977546461711391482970112.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 5] +
                   ( li_Real_s(        12427623510537921020035072.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 6] +
                   ( li_Real_s(        -1694675933233268081557504.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 7] +
                   ( li_Real_s(       -15252083396813300426604544.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 8] +
                   ( li_Real_s(       102951562963184668651814912.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 9] +
                   ( li_Real_s(      -297415626439870677627437056.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[10] +
                   ( li_Real_s(       476627606617898468520230912.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[11] +
                   ( li_Real_s(      -457562502457606425613959168.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[12] +
                   ( li_Real_s(       263098438949276283012382720.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[13] +
                   ( li_Real_s(       -83886458799064813452394496.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[14] +
                   ( li_Real_s(        11439062562995822705770496.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[15] +
                   ( li_Real_s(        44061574295844463935750144.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[16] +
                   ( li_Real_s(      -297415626605117654555426816.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[17] +
                   ( li_Real_s(       859200699371449683047088128.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[18] +
                   ( li_Real_s(     -1376924198095735970454306816.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[19] +
                   ( li_Real_s(      1321847230433682537077276672.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[20] +
                   ( li_Real_s(      -760062157578602946513338368.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[21] +
                   ( li_Real_s(       242338658940731160583471104.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[22] +
                   ( li_Real_s(       -33046180762251599538028544.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[23] +
                   ( li_Real_s(       -70611497306200620937510912.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[24] +
                   ( li_Real_s(       476627606994690176962265088.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[25] +
                   ( li_Real_s(     -1376924198431467722827104256.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[26] +
                   ( li_Real_s(      2206609292922208699547648000.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[27] +
                   ( li_Real_s(     -2118344921564871923842678784.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[28] +
                   ( li_Real_s(      1218048329991407834056622080.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[29] +
                   ( li_Real_s(      -388363235642930536550236160.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[30] +
                   ( li_Real_s(        52958623037162830870609920.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[31] +
                   ( li_Real_s(        67787037434271858228723712.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[32] +
                   ( li_Real_s(      -457562502851461867324309504.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[33] +
                   ( li_Real_s(      1321847230864985214525898752.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[34] +
                   ( li_Real_s(     -2118344921746543130588479488.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[35] +
                   ( li_Real_s(      2033611125167382681012404224.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[36] +
                   ( li_Real_s(     -1169326397028702131379503104.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[37] +
                   ( li_Real_s(       372828706283819557963431936.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[38] +
                   ( li_Real_s(       -50840278123752414366400512.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[39] +
                   ( li_Real_s(       -38977546530677742939144192.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[40] +
                   ( li_Real_s(       263098439178260746411704320.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[41] +
                   ( li_Real_s(      -760062157844581543781072896.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[42] +
                   ( li_Real_s(      1218048330131019422505107456.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[43] +
                   ( li_Real_s(     -1169326397064490135351984128.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[44] +
                   ( li_Real_s(       672362678329696117491499008.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[45] +
                   ( li_Real_s(      -214376506120949180630302720.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[46] +
                   ( li_Real_s(        29233159921722084365959168.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[47] +
                   ( li_Real_s(        12427623532160439950508032.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[48] +
                   ( li_Real_s(       -83886458872174365240197120.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[49] +
                   ( li_Real_s(       242338659029560120875941888.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[50] +
                   ( li_Real_s(      -388363235696580656671752192.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[51] +
                   ( li_Real_s(       372828706305257148487041024.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[52] +
                   ( li_Real_s(      -214376506127040990444257280.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[53] +
                   ( li_Real_s(        68351929484427491071229952.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[54] +
                   ( li_Real_s(        -9320717655609031262208000.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[55] +
                   ( li_Real_s(        -1694675936165931343937536.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[56] +
                   ( li_Real_s(        11439062573150083171221504.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[57] +
                   ( li_Real_s(       -33046180775321142070083584.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[58] +
                   ( li_Real_s(        52958623046317502122426368.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[59] +
                   ( li_Real_s(       -50840278128589939111100416.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[60] +
                   ( li_Real_s(        29233159923695497284419584.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[61] +
                   ( li_Real_s(        -9320717655974502914326528.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[62] +
                   ( li_Real_s(         1271006952888411654979584.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[63];
        liVC[55] = ( li_Real_s(          -80698854214566183698432.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 0] +
                   ( li_Real_s(          544717266014920828256256.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 1] +
                   ( li_Real_s(        -1573627657695555315826688.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 2] +
                   ( li_Real_s(         2521839195551296338788352.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 3] +
                   ( li_Real_s(        -2420965628118223481208832.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 4] +
                   ( li_Real_s(         1392055236281759191531520.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 5] +
                   ( li_Real_s(         -443843698521021771415552.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 6] +
                   ( li_Real_s(           60524140701439332712448.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 7] +
                   ( li_Real_s(          564891980029674307715072.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 8] +
                   ( li_Real_s(        -3813020865945213390028800.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 9] +
                   ( li_Real_s(        11015393615173345823686656.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[10] +
                   ( li_Real_s(       -17652874386742605764362240.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[11] +
                   ( li_Real_s(        16946759413497291295686656.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[12] +
                   ( li_Real_s(        -9744386663212545904476160.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[13] +
                   ( li_Real_s(         3106905892485767421231104.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[14] +
                   ( li_Real_s(         -423668985285708957614080.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[15] +
                   ( li_Real_s(        -1694675940803565626327040.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[16] +
                   ( li_Real_s(        11439062603040738416525312.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[17] +
                   ( li_Real_s(       -33046180860471209470459904.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[18] +
                   ( li_Real_s(        52958623183046016464060416.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[19] +
                   ( li_Real_s(       -50840278260897093859147776.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[20] +
                   ( li_Real_s(        29233160000465117122658304.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[21] +
                   ( li_Real_s(        -9320717680645059203039232.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[22] +
                   ( li_Real_s(         1271006956265047834230784.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[23] +
                   ( li_Real_s(         2824459901420055251910656.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[24] +
                   ( li_Real_s(       -19065104339118737909088256.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[25] +
                   ( li_Real_s(        55076968102050559151833088.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[26] +
                   ( li_Real_s(       -88264371971548228955930624.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[27] +
                   ( li_Real_s(        84733797098955774198022144.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[28] +
                   ( li_Real_s(       -48721933331374107543994368.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[29] +
                   ( li_Real_s(        15534529466524324646092800.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[30] +
                   ( li_Real_s(        -2118344926909713195466752.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[31] +
                   ( li_Real_s(        -2824459900820810140483584.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[32] +
                   ( li_Real_s(        19065104334971053631602688.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[33] +
                   ( li_Real_s(       -55076968088911962135592960.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[34] +
                   ( li_Real_s(        88264371948170086308642816.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[35] +
                   ( li_Real_s(       -84733797074335338030170112.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[36] +
                   ( li_Real_s(        48721933316133201345773568.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[37] +
                   ( li_Real_s(       -15534529461392459350147072.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[38] +
                   ( li_Real_s(         2118344926186214411730944.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[39] +
                   ( li_Real_s(         1694675939893220195958784.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[40] +
                   ( li_Real_s(       -11439062596806266968866816.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[41] +
                   ( li_Real_s(        33046180840554372377083904.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[42] +
                   ( li_Real_s(       -52958623147109363673464832.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[43] +
                   ( li_Real_s(        50840278222552295855357952.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[44] +
                   ( li_Real_s(       -29233159976476732637052928.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[45] +
                   ( li_Real_s(         9320717672504325576851456.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[46] +
                   ( li_Real_s(        -1271006955111848309948416.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[47] +
                   ( li_Real_s(         -564891979716252424732672.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[48] +
                   ( li_Real_s(         3813020863879816767602688.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[49] +
                   ( li_Real_s(       -11015393608327526583631872.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[50] +
                   ( li_Real_s(        17652874373694239568560128.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[51] +
                   ( li_Real_s(       -16946759398893863470891008.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[52] +
                   ( li_Real_s(         9744386653739572478869504.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[53] +
                   ( li_Real_s(        -3106905889187207841841152.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[54] +
                   ( li_Real_s(          423668984811216472899584.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[55] +
                   ( li_Real_s(           80698854205819113701376.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[56] +
                   ( li_Real_s(         -544717265995777487929344.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[57] +
                   ( li_Real_s(         1573627657518228732641280.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[58] +
                   ( li_Real_s(        -2521839194896377713786880.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[59] +
                   ( li_Real_s(         2420965627090219300814848.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[60] +
                   ( li_Real_s(        -1392055235475555443802112.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[61] +
                   ( li_Real_s(          443843698206961414701056.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[62] +
                   ( li_Real_s(          -60524140653479311966208.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[63];
        liVC[56] = ( li_Real_s(       -14525793653289855813156864.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 0] +
                   ( li_Real_s(       101680555567526310804717568.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 1] +
                   ( li_Real_s(      -305041666688107435247271936.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 2] +
                   ( li_Real_s(       508402777789974047151357952.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 3] +
                   ( li_Real_s(      -508402777766251740184707072.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 4] +
                   ( li_Real_s(       305041666645597395139690496.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 5] +
                   ( li_Real_s(      -101680555543963639182524416.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 6] +
                   ( li_Real_s(        14525793648514934511763456.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 7] +
                   ( li_Real_s(                 97869057196329968.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 8] +
                   ( li_Real_s(               -653696543462439424.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 9] +
                   ( li_Real_s(               1875622919818321664.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[10] +
                   ( li_Real_s(              -2983049340894752256.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[11] +
                   ( li_Real_s(               2836472188823951872.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[12] +
                   ( li_Real_s(              -1613678275386223616.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[13] +
                   ( li_Real_s(                509324838070302208.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[14] +
                   ( li_Real_s(                -68864844165489304.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[15] +
                   ( li_Real_s(               -259443044980521952.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[16] +
                   ( li_Real_s(               1739509105851291904.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[17] +
                   ( li_Real_s(              -5001748372081496064.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[18] +
                   ( li_Real_s(               7962436074701275136.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[19] +
                   ( li_Real_s(              -7572420077678152704.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[20] +
                   ( li_Real_s(               4306721790030465024.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[21] +
                   ( li_Real_s(              -1358654188448757760.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[22] +
                   ( li_Real_s(                183598712605895648.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[23] +
                   ( li_Real_s(                381823141294184896.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[24] +
                   ( li_Real_s(              -2570201912373186560.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[25] +
                   ( li_Real_s(               7407301590745792512.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[26] +
                   ( li_Real_s(             -11804605563214542848.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[27] +
                   ( li_Real_s(              11229245696476532736.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[28] +
                   ( li_Real_s(              -6384991481965202432.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[29] +
                   ( li_Real_s(               2013347836558009600.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[30] +
                   ( li_Real_s(               -271919307521586400.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[31] +
                   ( li_Real_s(               -336557667026845952.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[32] +
                   ( li_Real_s(               2275068761653450496.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[33] +
                   ( li_Real_s(              -6573568348029267968.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[34] +
                   ( li_Real_s(              10489693540882302976.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[35] +
                   ( li_Real_s(              -9982878417843433472.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[36] +
                   ( li_Real_s(               5675821150484192256.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[37] +
                   ( li_Real_s(              -1789098972138833152.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[38] +
                   ( li_Real_s(                241519952018434368.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[39] +
                   ( li_Real_s(                177794093988923456.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[40] +
                   ( li_Real_s(              -1207230882750533888.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[41] +
                   ( li_Real_s(               3498082790183095296.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[42] +
                   ( li_Real_s(              -5590784626901720064.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[43] +
                   ( li_Real_s(               5324211158344047616.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[44] +
                   ( li_Real_s(              -3027411517376804864.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[45] +
                   ( li_Real_s(                954092773180031232.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[46] +
                   ( li_Real_s(               -128753788667038576.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[47] +
                   ( li_Real_s(                -52225425808362848.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[48] +
                   ( li_Real_s(                356244262652094016.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[49] +
                   ( li_Real_s(              -1035377780817377792.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[50] +
                   ( li_Real_s(               1657695999025636352.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[51] +
                   ( li_Real_s(              -1579990456080264704.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[52] +
                   ( li_Real_s(                898635145100618880.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[53] +
                   ( li_Real_s(               -283189146928625344.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[54] +
                   ( li_Real_s(                 38207402856281880.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[55] +
                   ( li_Real_s(                  6600808479442511.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[56] +
                   ( li_Real_s(                -45229668428923440.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[57] +
                   ( li_Real_s(                131852499406678816.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[58] +
                   ( li_Real_s(               -211486748088742176.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[59] +
                   ( li_Real_s(                201760715600899616.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[60] +
                   ( li_Real_s(               -114793787397083328.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[61] +
                   ( li_Real_s(                 36176317016749696.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[62] +
                   ( li_Real_s(                 -4880136589021589.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[63];
        liVC[57] = ( li_Real_s(        37663307762323994999521280.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 0] +
                   ( li_Real_s(      -263643154370760400674226176.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 1] +
                   ( li_Real_s(       790929463215023073215381504.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 2] +
                   ( li_Real_s(     -1318215772176450323287638016.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 3] +
                   ( li_Real_s(      1318215772300036254883381248.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 4] +
                   ( li_Real_s(      -790929463436705508095950848.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 5] +
                   ( li_Real_s(       263643154492391915991859200.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 6] +
                   ( li_Real_s(       -37663307785850326903422976.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 7] +
                   ( li_Real_s(      -101680555351798178065154048.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 8] +
                   ( li_Real_s(       711763887681254717374070784.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 9] +
                   ( li_Real_s(     -2135291663658041782229270528.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[10] +
                   ( li_Real_s(      3558819440294917629162815488.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[11] +
                   ( li_Real_s(     -3558819440967224459326914560.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[12] +
                   ( li_Real_s(      2135291664869601341457039360.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[13] +
                   ( li_Real_s(      -711763888352285151977275392.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[14] +
                   ( li_Real_s(       101680555483574990251491328.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[15] +
                   ( li_Real_s(       152520833020752957815128064.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[16] +
                   ( li_Real_s(     -1067645831736538356762279936.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[17] +
                   ( li_Real_s(      3202937496787638419078512640.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[18] +
                   ( li_Real_s(     -5338229163437052217765396480.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[19] +
                   ( li_Real_s(      5338229165003225167671853056.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[20] +
                   ( li_Real_s(     -3202937499624323443159203840.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[21] +
                   ( li_Real_s(      1067645833323755546907508736.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[22] +
                   ( li_Real_s(      -152520833337457730188738560.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[23] +
                   ( li_Real_s(      -169467592325574088177221632.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[24] +
                   ( li_Real_s(      1186273147174176319548162048.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[25] +
                   ( li_Real_s(     -3558819443803557639686717440.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[26] +
                   ( li_Real_s(      5931365742614603675553759232.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[27] +
                   ( li_Real_s(     -5931365744668019705751011328.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[28] +
                   ( li_Real_s(      3558819447543352927520292864.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[29] +
                   ( li_Real_s(     -1186273149290215309383303168.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[30] +
                   ( li_Real_s(       169467592755226810989412352.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[31] +
                   ( li_Real_s(       127100694331497010742427648.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[32] +
                   ( li_Real_s(      -889704861138935035329511424.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[33] +
                   ( li_Real_s(      2669114585417378332476964864.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[34] +
                   ( li_Real_s(     -4448524311507011674809827328.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[35] +
                   ( li_Real_s(      4448524313142557211359182848.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[36] +
                   ( li_Real_s(     -2669114588414120363724636160.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[37] +
                   ( li_Real_s(       889704862855236814720991232.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[38] +
                   ( li_Real_s(      -127100694686601247463571456.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[39] +
                   ( li_Real_s(       -61008333324373182824579072.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[40] +
                   ( li_Real_s(       427058333721751109058428928.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[41] +
                   ( li_Real_s(     -1281175002227705571939713024.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[42] +
                   ( li_Real_s(      2135291671646397828545118208.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[43] +
                   ( li_Real_s(     -2135291672436217712706846720.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[44] +
                   ( li_Real_s(      1281175003684384481027817472.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[45] +
                   ( li_Real_s(      -427058334567018608694657024.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[46] +
                   ( li_Real_s(        61008333502780248785158144.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[47] +
                   ( li_Real_s(        16946759268731909595725824.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[48] +
                   ( li_Real_s(      -118627315019852097173585920.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[49] +
                   ( li_Real_s(       355881945375731889563762688.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[50] +
                   ( li_Real_s(      -593136575990197747152060416.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[51] +
                   ( li_Real_s(       593136576204511736139612160.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[52] +
                   ( li_Real_s(      -355881945773782998926229504.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[53] +
                   ( li_Real_s(       118627315254046458982170624.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[54] +
                   ( li_Real_s(       -16946759319188779514724352.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[55] +
                   ( li_Real_s(        -2075113381098287483846656.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[56] +
                   ( li_Real_s(        14525793686047313681711104.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[57] +
                   ( li_Real_s(       -43577381098808286984011776.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[58] +
                   ( li_Real_s(        72628968543391727396847616.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[59] +
                   ( li_Real_s(       -72628968568693001780461568.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[60] +
                   ( li_Real_s(        43577381146137563865546752.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[61] +
                   ( li_Real_s(       -14525793714283032128520192.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[62] +
                   ( li_Real_s(         2075113387309051785773056.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[63];
        liVC[58] = ( li_Real_s(       -37847762209931343825993728.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 0] +
                   ( li_Real_s(       264934335565402722009088000.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 1] +
                   ( li_Real_s(      -794803006973128656338026496.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 2] +
                   ( li_Real_s(      1324671678699970901277933568.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 3] +
                   ( li_Real_s(     -1324671679046088640486703104.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 4] +
                   ( li_Real_s(       794803007593997308897787904.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 5] +
                   ( li_Real_s(      -264934335907020744240922624.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 6] +
                   ( li_Real_s(        37847762276768559734456320.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 7] +
                   ( li_Real_s(       161962598552319248578904064.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 8] +
                   ( li_Real_s(     -1133738190466347739815870464.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 9] +
                   ( li_Real_s(      3401214573056194984116486144.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[10] +
                   ( li_Real_s(     -5668690957472285137542578176.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[11] +
                   ( li_Real_s(      5668690959405505855126241280.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[12] +
                   ( li_Real_s(     -3401214576534951368109064192.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[13] +
                   ( li_Real_s(      1133738192393146209981693952.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[14] +
                   ( li_Real_s(      -161962598933581743098167296.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[15] +
                   ( li_Real_s(      -319204314111331374825734144.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[16] +
                   ( li_Real_s(      2234430200385886638026260480.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[17] +
                   ( li_Real_s(     -6703290605428216127796805632.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[18] +
                   ( li_Real_s(     11172151014981587014512541696.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[19] +
                   ( li_Real_s(    -11172151019639802166004154368.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[20] +
                   ( li_Real_s(      6703290613836193640027783168.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[21] +
                   ( li_Real_s(     -2234430205073468645584142336.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[22] +
                   ( li_Real_s(       319204315049149715974193152.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[23] +
                   ( li_Real_s(       382916058786879400314929152.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[24] +
                   ( li_Real_s(     -2680412413913783820965904384.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[25] +
                   ( li_Real_s(      8041237247920209337545392128.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[26] +
                   ( li_Real_s(    -13402062088200610380179832832.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[27] +
                   ( li_Real_s(     13402062094524609837007896576.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[28] +
                   ( li_Real_s(     -8041237259369316165437358080.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[29] +
                   ( li_Real_s(      2680412420338852585642393600.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[30] +
                   ( li_Real_s(      -382916060086840862646992896.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[31] +
                   ( li_Real_s(      -297778768667664260305780736.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[32] +
                   ( li_Real_s(      2084451382845622171071414272.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[33] +
                   ( li_Real_s(     -6253354153944783668104921088.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[34] +
                   ( li_Real_s(     10422256930335601060019699712.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[35] +
                   ( li_Real_s(    -10422256935545436797120020480.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[36] +
                   ( li_Real_s(      6253354163405173028512858112.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[37] +
                   ( li_Real_s(     -2084451388189932578295250944.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[38] +
                   ( li_Real_s(       297778769761422212453105664.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[39] +
                   ( li_Real_s(       145984225674453875609829376.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[40] +
                   ( li_Real_s(     -1021889580902480361883172864.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[41] +
                   ( li_Real_s(      3065668745566329097785704448.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[42] +
                   ( li_Real_s(     -5109447912931073171738591232.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[43] +
                   ( li_Real_s(      5109447915529144381382590464.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[44] +
                   ( li_Real_s(     -3065668750298554026210361344.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[45] +
                   ( li_Real_s(      1021889583593958932597440512.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[46] +
                   ( li_Real_s(      -145984226231781184264732672.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[47] +
                   ( li_Real_s(       -41116065789785313267154944.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[48] +
                   ( li_Real_s(       287812460887079150510145536.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[49] +
                   ( li_Real_s(      -863437383506897545537257472.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[50] +
                   ( li_Real_s(      1439062306899636193568227328.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[51] +
                   ( li_Real_s(     -1439062307626424649522348032.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[52] +
                   ( li_Real_s(       863437384834820344477908992.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[53] +
                   ( li_Real_s(      -287812461647564545479147520.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[54] +
                   ( li_Real_s(        41116065949137189883346944.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[55] +
                   ( li_Real_s(         5084027764049884544499712.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[56] +
                   ( li_Real_s(       -35588194395168528299720704.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[57] +
                   ( li_Real_s(       106764583293568697233309696.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[58] +
                   ( li_Real_s(      -177940972287830457449447424.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[59] +
                   ( li_Real_s(       177940972376079597156958208.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[60] +
                   ( li_Real_s(      -106764583455297855427706880.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[61] +
                   ( li_Real_s(        35588194488410412870008832.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[62] +
                   ( li_Real_s(        -5084027783805865448964096.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[63];
        liVC[59] = ( li_Real_s(        19508947775225985000013824.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 0] +
                   ( li_Real_s(      -136562634499202533480726528.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 1] +
                   ( li_Real_s(       409687903704515261925163008.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 2] +
                   ( li_Real_s(      -682813173145155347370999808.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 3] +
                   ( li_Real_s(       682813173397543706041516032.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 4] +
                   ( li_Real_s(      -409687904157115479603806208.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 5] +
                   ( li_Real_s(       136562634748159264821346304.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 6] +
                   ( li_Real_s(       -19508947823969259604672512.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 7] +
                   ( li_Real_s(      -102971736795716363990597632.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 8] +
                   ( li_Real_s(       720802158025789897495805952.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 9] +
                   ( li_Real_s(     -2162406475315087870290558976.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[10] +
                   ( li_Real_s(      3604010793941482554731266048.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[11] +
                   ( li_Real_s(     -3604010795334148171728158720.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[12] +
                   ( li_Real_s(      2162406477821380370462932992.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[13] +
                   ( li_Real_s(      -720802159414886912065798144.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[14] +
                   ( li_Real_s(       102971737071187079500660736.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[15] +
                   ( li_Real_s(       237799346039109731150200832.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[16] +
                   ( li_Real_s(     -1664595423498914308103864320.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[17] +
                   ( li_Real_s(      4993786273685020155995750400.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[18] +
                   ( li_Real_s(     -8322977127151160779444584448.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[19] +
                   ( li_Real_s(      8322977130465545122886975488.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[20] +
                   ( li_Real_s(     -4993786279670527261631578112.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[21] +
                   ( li_Real_s(      1664595426841602554746372096.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[22] +
                   ( li_Real_s(      -237799346710678445414678528.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[23] +
                   ( li_Real_s(      -313918539601885757811195904.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[24] +
                   ( li_Real_s(      2197429779051786881093074944.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[25] +
                   ( li_Real_s(     -6592289341763150542253588480.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[26] +
                   ( li_Real_s(     10987148909003706613188526080.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[27] +
                   ( li_Real_s(    -10987148913445062887310622720.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[28] +
                   ( li_Real_s(      6592289349811805455504113664.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[29] +
                   ( li_Real_s(     -2197429783581334433123270656.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[30] +
                   ( li_Real_s(       313918540524137694369939456.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[31] +
                   ( li_Real_s(       256723227417866155000332288.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[32] +
                   ( li_Real_s(     -1797062593586573657361088512.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[33] +
                   ( li_Real_s(      5391187784784048703586435072.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[34] +
                   ( li_Real_s(     -8985312979770575784180187136.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[35] +
                   ( li_Real_s(      8985312983376749622913400832.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[36] +
                   ( li_Real_s(     -5391187791342290316619153408.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[37] +
                   ( li_Real_s(      1797062597306667346092359680.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[38] +
                   ( li_Real_s(      -256723228185892756626866176.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[39] +
                   ( li_Real_s(      -129763756358342045142614016.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[40] +
                   ( li_Real_s(       908346295412299904615186432.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[41] +
                   ( li_Real_s(     -2725038888358578786014330880.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[42] +
                   ( li_Real_s(      4541731483221456380525281280.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[43] +
                   ( li_Real_s(     -4541731484990998849395884032.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[44] +
                   ( li_Real_s(      2725038891588621241757466624.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[45] +
                   ( li_Real_s(      -908346297259833344584056832.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[46] +
                   ( li_Real_s(       129763756745376391592148992.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[47] +
                   ( li_Real_s(        37303045029401382487064576.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[48] +
                   ( li_Real_s(      -261121315480291957735948288.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[49] +
                   ( li_Real_s(       783363947066849523895631872.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[50] +
                   ( li_Real_s(     -1305606579196911183906996224.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[51] +
                   ( li_Real_s(      1305606579683605058139717632.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[52] +
                   ( li_Real_s(      -783363947958698726995787776.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[53] +
                   ( li_Real_s(       261121315994899820857786368.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[54] +
                   ( li_Real_s(       -37303045138854294698590208.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[55] +
                   ( li_Real_s(        -4680533504874203431567360.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[56] +
                   ( li_Real_s(        32763734570069950092804096.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[57] +
                   ( li_Real_s(       -98291203790022806633185280.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[58] +
                   ( li_Real_s(       163818673076805276989915136.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[59] +
                   ( li_Real_s(      -163818673134923125171945472.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[60] +
                   ( li_Real_s(        98291203896935039530696704.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[61] +
                   ( li_Real_s(       -32763734632302303929958400.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[62] +
                   ( li_Real_s(         4680533518314264739184640.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[63];
        liVC[60] = ( li_Real_s(        -5648919733241933924925440.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 0] +
                   ( li_Real_s(        39542438155413678247116800.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 1] +
                   ( li_Real_s(      -118627314530821090716942336.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 2] +
                   ( li_Real_s(       197712190978103904711999488.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 3] +
                   ( li_Real_s(      -197712191052866503512686592.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 4] +
                   ( li_Real_s(       118627314664667235326361600.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 5] +
                   ( li_Real_s(       -39542438228766625831583744.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 6] +
                   ( li_Real_s(         5648919747509521076977664.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 7] +
                   ( li_Real_s(        33590897736960968501493760.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 8] +
                   ( li_Real_s(      -235136284302985518278246400.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 9] +
                   ( li_Real_s(       705408853293459928596348928.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[10] +
                   ( li_Real_s(     -1175681422682134329023266816.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[11] +
                   ( li_Real_s(      1175681423077677177484869632.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[12] +
                   ( li_Real_s(      -705408854005090242372042752.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[13] +
                   ( li_Real_s(       235136284697119926704406528.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[14] +
                   ( li_Real_s(       -33590897815007632440688640.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[15] +
                   ( li_Real_s(       -85944278982257065687252992.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[16] +
                   ( li_Real_s(       601609953266090886119292928.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[17] +
                   ( li_Real_s(     -1804829860782006398923833344.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[18] +
                   ( li_Real_s(      3008049769247255781751914496.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[19] +
                   ( li_Real_s(     -3008049770142837139633602560.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[20] +
                   ( li_Real_s(      1804829862401716219254145024.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[21] +
                   ( li_Real_s(      -601609954173410011663826944.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[22] +
                   ( li_Real_s(        85944279165447934941593600.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[23] +
                   ( li_Real_s(       122964878135867883871272960.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[24] +
                   ( li_Real_s(      -860754147538987627883528192.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[25] +
                   ( li_Real_s(      2582262444026976732549480448.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[26] +
                   ( li_Real_s(     -4303770741785732585770450944.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[27] +
                   ( li_Real_s(      4303770742919376902763315200.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[28] +
                   ( li_Real_s(     -2582262446089018431466635264.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[29] +
                   ( li_Real_s(       860754148708737020514533376.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[30] +
                   ( li_Real_s(      -122964878377216475784019968.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[31] +
                   ( li_Real_s(      -106522486801654372808785920.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[32] +
                   ( li_Real_s(       745657408143599462747471872.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[33] +
                   ( li_Real_s(     -2236972225650086002384961536.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[34] +
                   ( li_Real_s(      3728287044183481905187913728.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[35] +
                   ( li_Real_s(     -3728287045044423149236518912.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[36] +
                   ( li_Real_s(      2236972227226423112656486400.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[37] +
                   ( li_Real_s(      -745657409050885946540556288.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[38] +
                   ( li_Real_s(       106522486993544938839343104.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[39] +
                   ( li_Real_s(        55984829748635776210436096.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[40] +
                   ( li_Real_s(      -391893808529930576388423680.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[41] +
                   ( li_Real_s(      1175681426225733449191260160.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[42] +
                   ( li_Real_s(     -1959469044421542808138022912.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[43] +
                   ( li_Real_s(      1959469044811870260632223744.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[44] +
                   ( li_Real_s(     -1175681426946129069663584256.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[45] +
                   ( li_Real_s(       391893808951865895804731392.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[46] +
                   ( li_Real_s(       -55984829840502412252545024.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[47] +
                   ( li_Real_s(       -16543265016182150229131264.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[48] +
                   ( li_Real_s(       115802855201201458878873600.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[49] +
                   ( li_Real_s(      -347408565789350167316529152.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[50] +
                   ( li_Real_s(       579014276513775920313532416.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[51] +
                   ( li_Real_s(      -579014276611796900893425664.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[52] +
                   ( li_Real_s(       347408565972061237184299008.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[53] +
                   ( li_Real_s(      -115802855310513564882567168.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[54] +
                   ( li_Real_s(        16543265040803722415833088.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[55] +
                   ( li_Real_s(         2118344911558076566339584.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[56] +
                   ( li_Real_s(       -14828414392414338193293312.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[57] +
                   ( li_Real_s(        44485243200717942167699456.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[58] +
                   ( li_Real_s(       -74142072025137382275678208.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[59] +
                   ( li_Real_s(        74142072035726435165405184.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[60] +
                   ( li_Real_s(       -44485243220693302485450752.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[61] +
                   ( li_Real_s(        14828414404666544153952256.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[62] +
                   ( li_Real_s(        -2118344914424446471634944.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[63];
        liVC[61] = ( li_Real_s(          928036815919636753154048.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 0] +
                   ( li_Real_s(        -6496257714421745504485376.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 1] +
                   ( li_Real_s(        19488773151901367773691904.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 2] +
                   ( li_Real_s(       -32481288598612489669705728.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 3] +
                   ( li_Real_s(        32481288607485282217885696.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 4] +
                   ( li_Real_s(       -19488773167693009038344192.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 5] +
                   ( li_Real_s(         6496257722956839806566400.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 6] +
                   ( li_Real_s(         -928036817534398695997440.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 7] +
                   ( li_Real_s(        -5951540458796705504034816.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 8] +
                   ( li_Real_s(        41660783231005014785785856.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 9] +
                   ( li_Real_s(      -124982349743489946696548352.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[10] +
                   ( li_Real_s(       208303916303347216830955520.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[11] +
                   ( li_Real_s(      -208303916344055707136425984.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[12] +
                   ( li_Real_s(       124982349816544454183485440.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[13] +
                   ( li_Real_s(       -41660783271198297994297344.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[14] +
                   ( li_Real_s(         5951540466644043471781888.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[15] +
                   ( li_Real_s(        16341517889429248201981952.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[16] +
                   ( li_Real_s(      -114390625279127646004838400.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[17] +
                   ( li_Real_s(       343171875963300710434471936.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[18] +
                   ( li_Real_s(      -571953126749830456209833984.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[19] +
                   ( li_Real_s(       571953126824289864679161856.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[20] +
                   ( li_Real_s(      -343171876098568953075335168.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[21] +
                   ( li_Real_s(       114390625355521335945592832.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[22] +
                   ( li_Real_s(       -16341517905014387439042560.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[23] +
                   ( li_Real_s(       -24915771125750711344693248.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[24] +
                   ( li_Real_s(       174410397960580239466692608.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[25] +
                   ( li_Real_s(      -523231194056918037673541632.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[26] +
                   ( li_Real_s(       872051990274370512013492224.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[27] +
                   ( li_Real_s(      -872051990341479616531660800.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[28] +
                   ( li_Real_s(       523231194181685050915946496.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[29] +
                   ( li_Real_s(      -174410398034501986750038016.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[30] +
                   ( li_Real_s(        24915771142015812624187392.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[31] +
                   ( li_Real_s(        22797426228456030042324992.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[32] +
                   ( li_Real_s(      -159581983671759337779363840.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[33] +
                   ( li_Real_s(       478745951161502133435498496.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[34] +
                   ( li_Real_s(      -797909918734400100147134464.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[35] +
                   ( li_Real_s(       797909918759666602475520000.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[36] +
                   ( li_Real_s(      -478745951212075682583543808.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[37] +
                   ( li_Real_s(       159581983706049703835598848.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[38] +
                   ( li_Real_s(       -22797426237439439473213440.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[39] +
                   ( li_Real_s(       -12528497076021349845041152.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[40] +
                   ( li_Real_s(        87699479571485673547366400.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[41] +
                   ( li_Real_s(      -263098438787802658192228352.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[42] +
                   ( li_Real_s(       438497398036467962121027584.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[43] +
                   ( li_Real_s(      -438497398033121254884507648.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[44] +
                   ( li_Real_s(       263098438785231759488319488.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[45] +
                   ( li_Real_s(       -87699479574374657529217024.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[46] +
                   ( li_Real_s(        12528497078134362085523456.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[47] +
                   ( li_Real_s(         3833195564419099417116672.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[48] +
                   ( li_Real_s(       -26832368962847106270232576.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[49] +
                   ( li_Real_s(        80497106909156277068234752.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[50] +
                   ( li_Real_s(      -134161844861882859150901248.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[51] +
                   ( li_Real_s(       134161844856389905216962560.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[52] +
                   ( li_Real_s(       -80497106900495630134673408.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[53] +
                   ( li_Real_s(        26832368959598496086753280.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[54] +
                   ( li_Real_s(        -3833195564338169348358144.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[55] +
                   ( li_Real_s(         -504367837589113210404864.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[56] +
                   ( li_Real_s(         3530574864675566774124544.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[57] +
                   ( li_Real_s(       -10591724596541207716298752.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[58] +
                   ( li_Real_s(        17652874328875192830394368.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[59] +
                   ( li_Real_s(       -17652874327672668559507456.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[60] +
                   ( li_Real_s(        10591724594556595670614016.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[61] +
                   ( li_Real_s(        -3530574863805217958264832.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[62] +
                   ( li_Real_s(          504367837500436094386176.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[63];
        liVC[62] = ( li_Real_s(          -80698853916197657772032.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 0] +
                   ( li_Real_s(          564891977523440228761600.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 1] +
                   ( li_Real_s(        -1694675932922338487566336.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 2] +
                   ( li_Real_s(         2824459888642190928248832.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 3] +
                   ( li_Real_s(        -2824459888824109636780032.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 4] +
                   ( li_Real_s(         1694675933226132261830656.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 5] +
                   ( li_Real_s(         -564891977662195187056640.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 6] +
                   ( li_Real_s(           80698853933031983415296.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 7] +
                   ( li_Real_s(          544717264712029077241856.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 8] +
                   ( li_Real_s(        -3813020853760600014061568.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 9] +
                   ( li_Real_s(        11439062563136588111413248.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[10] +
                   ( li_Real_s(       -19065104273440430878621696.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[11] +
                   ( li_Real_s(        19065104273021695189581824.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[12] +
                   ( li_Real_s(       -11439062562332288913244160.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[13] +
                   ( li_Real_s(         3813020853243649160380416.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[14] +
                   ( li_Real_s(         -544717264580644551262208.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[15] +
                   ( li_Real_s(        -1573627655138775511597056.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[16] +
                   ( li_Real_s(        11015393588154913450360832.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[17] +
                   ( li_Real_s(       -33046180768418360826265600.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[18] +
                   ( li_Real_s(        55076967948510847028953088.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[19] +
                   ( li_Real_s(       -55076967943637029810601984.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[20] +
                   ( li_Real_s(        33046180759705195032608768.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[21] +
                   ( li_Real_s(       -11015393583369950515429376.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[22] +
                   ( li_Real_s(         1573627654193171889389568.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[23] +
                   ( li_Real_s(         2521839192420284507357184.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[24] +
                   ( li_Real_s(       -17652874350250182058180608.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[25] +
                   ( li_Real_s(        52958623055139777265270784.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[26] +
                   ( li_Real_s(       -88264371756223170307162112.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[27] +
                   ( li_Real_s(        88264371744038279368933376.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[28] +
                   ( li_Real_s(       -52958623033517047881400320.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[29] +
                   ( li_Real_s(        17652874338608232968224768.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[30] +
                   ( li_Real_s(        -2521839190216172789301248.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[31] +
                   ( li_Real_s(        -2420965625559977214083072.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[32] +
                   ( li_Real_s(        16946759381854912163872768.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[33] +
                   ( li_Real_s(       -50840278148115874050998272.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[34] +
                   ( li_Real_s(        84733796907997817366118400.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[35] +
                   ( li_Real_s(       -84733796893053684818116608.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[36] +
                   ( li_Real_s(        50840278121651342135001088.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[37] +
                   ( li_Real_s(       -16946759367697576822308864.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[38] +
                   ( li_Real_s(         2420965622923047146094592.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[39] +
                   ( li_Real_s(         1392055234958214284967936.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[40] +
                   ( li_Real_s(        -9744386646255323530133504.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[41] +
                   ( li_Real_s(        29233159939411401095774208.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[42] +
                   ( li_Real_s(       -48721933227637848343052288.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[43] +
                   ( li_Real_s(        48721933217587710769758208.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[44] +
                   ( li_Real_s(       -29233159921626989495058432.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[45] +
                   ( li_Real_s(         9744386636768932626694144.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[46] +
                   ( li_Real_s(        -1392055233206090429628416.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[47] +
                   ( li_Real_s(         -443843698137164505153536.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[48] +
                   ( li_Real_s(         3106905887418429177069568.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[49] +
                   ( li_Real_s(        -9320717662254259423412224.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[50] +
                   ( li_Real_s(        15534529435209202694881280.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[51] +
                   ( li_Real_s(       -15534529431656347765571584.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[52] +
                   ( li_Real_s(         9320717655969870792097792.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[53] +
                   ( li_Real_s(        -3106905884072469801730048.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[54] +
                   ( li_Real_s(          443843697522734872395776.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[55] +
                   ( li_Real_s(           60524140654900115668992.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[56] +
                   ( li_Real_s(         -423668984643402302750720.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[57] +
                   ( li_Real_s(         1271006953908702610980864.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[58] +
                   ( li_Real_s(        -2118344922886448483401728.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[59] +
                   ( li_Real_s(         2118344922367960568299520.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[60] +
                   ( li_Real_s(        -1271006952991793933713408.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[61] +
                   ( li_Real_s(          423668984155848486944768.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[62] +
                   ( li_Real_s(          -60524140565774527889408.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[63];
        liVC[63] = ( li_Real_s(            2882101941819136278528.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 0] +
                   ( li_Real_s(          -20174713588771308175360.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 1] +
                   ( li_Real_s(           60524140758026491527168.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 2] +
                   ( li_Real_s(         -100873567914213532237824.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 3] +
                   ( li_Real_s(          100873567891442756485120.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 4] +
                   ( li_Real_s(          -60524140715816526020608.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 5] +
                   ( li_Real_s(           20174713563812141727744.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 6] +
                   ( li_Real_s(           -2882101936298643685376.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 7] +
                   ( li_Real_s(          -20174713612288342884352.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 8] +
                   ( li_Real_s(          141222995264780533497856.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[ 9] +
                   ( li_Real_s(         -423668985727878055329792.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[10] +
                   ( li_Real_s(          706114976063583558828032.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[11] +
                   ( li_Real_s(         -706114975855063165042688.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[12] +
                   ( li_Real_s(          423668985349002816913408.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[13] +
                   ( li_Real_s(         -141222995049787422670848.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[14] +
                   ( li_Real_s(           20174713567649644675072.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[15] +
                   ( li_Real_s(           60524140861480534802432.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[16] +
                   ( li_Real_s(         -423668985976219372617728.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[17] +
                   ( li_Real_s(         1271006957703967105089536.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[18] +
                   ( li_Real_s(        -2118344928974071509549056.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[19] +
                   ( li_Real_s(         2118344928251774779785216.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[20] +
                   ( li_Real_s(        -1271006956402422631628800.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[21] +
                   ( li_Real_s(          423668985251145812279296.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[22] +
                   ( li_Real_s(          -60524140715654307119104.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[23] +
                   ( li_Real_s(         -100873568100480056295424.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[24] +
                   ( li_Real_s(          706114976620568339546112.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[25] +
                   ( li_Real_s(        -2118344929452850304516096.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[26] +
                   ( li_Real_s(         3530574881441807522070528.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[27] +
                   ( li_Real_s(        -3530574880144287164530688.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[28] +
                   ( li_Real_s(         2118344927124172723716096.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[29] +
                   ( li_Real_s(         -706114975335607405903872.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[30] +
                   ( li_Real_s(          100873567846677822308352.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[31] +
                   ( li_Real_s(          100873568072598286237696.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[32] +
                   ( li_Real_s(         -706114976427642972012544.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[33] +
                   ( li_Real_s(         2118344928845946192658432.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[34] +
                   ( li_Real_s(        -3530574880370189559398400.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[35] +
                   ( li_Real_s(         3530574879022608673669120.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[36] +
                   ( li_Real_s(        -2118344926432684868108288.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[37] +
                   ( li_Real_s(          706114975103319602626560.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[38] +
                   ( li_Real_s(         -100873567813954684583936.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[39] +
                   ( li_Real_s(          -60524140817815288414208.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[40] +
                   ( li_Real_s(          423668985676872969879552.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[41] +
                   ( li_Real_s(        -1271006956757074724257792.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[42] +
                   ( li_Real_s(         2118344927284792689426432.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[43] +
                   ( li_Real_s(        -2118344926465550494728192.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[44] +
                   ( li_Real_s(         1271006955291909981995008.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[45] +
                   ( li_Real_s(         -423668984875680442351616.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[46] +
                   ( li_Real_s(           60524140662545115512832.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[47] +
                   ( li_Real_s(           20174713595545918636032.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[48] +
                   ( li_Real_s(         -141222995153295933177856.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[49] +
                   ( li_Real_s(          423668985367375546155008.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[50] +
                   ( li_Real_s(         -706114975396372200554496.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[51] +
                   ( li_Real_s(          706114975125208500797440.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[52] +
                   ( li_Real_s(         -423668984882859614404608.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[53] +
                   ( li_Real_s(          141222994889027383984128.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[54] +
                   ( li_Real_s(          -20174713544629572075520.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[55] +
                   ( li_Real_s(           -2882101940590817050624.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[56] +
                   ( li_Real_s(           20174713581988749508608.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[57] +
                   ( li_Real_s(          -60524140732850651529216.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[58] +
                   ( li_Real_s(          100873567857643125473280.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[59] +
                   ( li_Real_s(         -100873567819788089032704.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[60] +
                   ( li_Real_s(           60524140665250600976384.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[61] +
                   ( li_Real_s(          -20174713545186617589760.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[62] +
                   ( li_Real_s(            2882101933529964216320.0 ) / li_Real_s(     73209999932589693839616245760.0 ) ) * liVS[63];

        /* Prepare interpolated value computation */
        liTX1 = ( liX + li_Real_s( 3.0 ) ) - liPXmm; 
        liTX2 = liTX1 * liTX1;
        liTX3 = liTX1 * liTX2;
        liTX4 = liTX1 * liTX3;
        liTX5 = liTX1 * liTX4;
        liTX6 = liTX1 * liTX5;
        liTX7 = liTX1 * liTX6;
        liTY1 = ( liY + li_Real_s( 3.0 ) ) - liPYmm; 
        liTY2 = liTY1 * liTY1; 
        liTY3 = liTY1 * liTY2; 
        liTY4 = liTY1 * liTY3; 
        liTY5 = liTY1 * liTY4; 
        liTY6 = liTY1 * liTY5; 
        liTY7 = liTY1 * liTY6;

        /* Compute interpolated value */
        liIV = liVC[ 0]                 + 
               liVC[ 1] * liTY1         + 
               liVC[ 2] * liTY2         + 
               liVC[ 3] * liTY3         + 
               liVC[ 4] * liTY4         + 
               liVC[ 5] * liTY5         + 
               liVC[ 6] * liTY6         + 
               liVC[ 7] * liTY7         +
               liVC[ 8] * liTX1         + 
               liVC[ 9] * liTY1 * liTX1 + 
               liVC[10] * liTY2 * liTX1 + 
               liVC[11] * liTY3 * liTX1 + 
               liVC[12] * liTY4 * liTX1 + 
               liVC[13] * liTY5 * liTX1 + 
               liVC[14] * liTY6 * liTX1 + 
               liVC[15] * liTY7 * liTX1 +
               liVC[16] * liTX2         + 
               liVC[17] * liTY1 * liTX2 + 
               liVC[18] * liTY2 * liTX2 + 
               liVC[19] * liTY3 * liTX2 + 
               liVC[20] * liTY4 * liTX2 + 
               liVC[21] * liTY5 * liTX2 + 
               liVC[22] * liTY6 * liTX2 + 
               liVC[23] * liTY7 * liTX2 +
               liVC[24] * liTX3         + 
               liVC[25] * liTY1 * liTX3 + 
               liVC[26] * liTY2 * liTX3 + 
               liVC[27] * liTY3 * liTX3 + 
               liVC[28] * liTY4 * liTX3 + 
               liVC[29] * liTY5 * liTX3 + 
               liVC[30] * liTY6 * liTX3 + 
               liVC[31] * liTY7 * liTX3 +
               liVC[32] * liTX4         + 
               liVC[33] * liTY1 * liTX4 + 
               liVC[34] * liTY2 * liTX4 + 
               liVC[35] * liTY3 * liTX4 + 
               liVC[36] * liTY4 * liTX4 + 
               liVC[37] * liTY5 * liTX4 + 
               liVC[38] * liTY6 * liTX4 + 
               liVC[39] * liTY7 * liTX4 +
               liVC[40] * liTX5         + 
               liVC[41] * liTY1 * liTX5 + 
               liVC[42] * liTY2 * liTX5 + 
               liVC[43] * liTY3 * liTX5 + 
               liVC[44] * liTY4 * liTX5 + 
               liVC[45] * liTY5 * liTX5 + 
               liVC[46] * liTY6 * liTX5 + 
               liVC[47] * liTY7 * liTX5 +
               liVC[48] * liTX6         + 
               liVC[49] * liTY1 * liTX6 + 
               liVC[50] * liTY2 * liTX6 + 
               liVC[51] * liTY3 * liTX6 + 
               liVC[52] * liTY4 * liTX6 + 
               liVC[53] * liTY5 * liTX6 + 
               liVC[54] * liTY6 * liTX6 + 
               liVC[55] * liTY7 * liTX6 +  
               liVC[56] * liTX7         + 
               liVC[57] * liTY1 * liTX7 + 
               liVC[58] * liTY2 * liTX7 + 
               liVC[59] * liTY3 * liTX7 + 
               liVC[60] * liTY4 * liTX7 + 
               liVC[61] * liTY5 * liTX7 + 
               liVC[62] * liTY6 * liTX7 + 
               liVC[63] * liTY7 * liTX7;

        /* Verify interpolated value */
        if ( liIV < li_Real_s( 0.0 ) ) {

            /* Clamp interpolated value */
            liIV = li_Real_s( 0.0 );

        } else if ( liIV > li_Real_s( 255.0 ) ) {

            /* Clamp interpolated value */
            liIV = li_Real_s( 255.0 );

        }

        /* Return interpolated value */
        return( li_C8_c( liIV ) );

    }

