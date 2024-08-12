# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    run_invalid_maps.sh                                :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/12 12:38:38 by llitovuo          #+#    #+#              #
#    Updated: 2024/08/12 12:47:59 by llitovuo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


R="\033[0;31m" # Red
G="\033[0;32m" # Green
Y="\033[0;33m" # yellow
B="\033[0;34m" # Blue
P="\033[0;35m" # Purple
C="\033[0;36m" # Cyan

RB="\033[1;31m" # Bold
GB="\033[1;32m"
YB="\033[1;33m"
BB="\033[1;34m"
PB="\033[1;35m"
CB="\033[1;36m"

RC="\033[0m" # Reset Color
FLL="**************"

run_maptest()
{
	printf "${GB}Testing:${RC} ./cub3D $1\n"
	#cat $1
	#printf "\n\n"
	printf "${BB}Output:\n${RC}"
	./cub3D "$1"
	printf "${RC}${RB}Exit Code: ${RC}$?\n"
	#leaks --atExit -- ./map_test "$1"
	#sleep 1
	printf "================================\n\n"
}

m1="maps/invalid/color_too_big.cub"
m2="maps/invalid/double_texture.cub"
m3="maps/invalid/empty.cub"
m4="maps/invalid/extra_char_line.cub"
m5="maps/invalid/extra_color_c.cub"
m6="maps/invalid/extra_color_code.cub"
m7="maps/invalid/extra_color_f.cub"
m8="maps/invalid/extra_comma.cub"
m9="maps/invalid/extra_path.cub"
m10="maps/invalid/invalid_color_letter.cub"
m11="maps/invalid/invalid_filename.cube"
m12="maps/invalid/invalid_map_symbol.cub"
m13="maps/invalid/invalid_texture_path.cub"
m14="maps/invalid/neg_number.cub"
m15="maps/invalid/nl_1.cub"
m16="maps/invalid/nl_2.cub"
m17="maps/invalid/nl_3.cub"
m18="maps/invalid/nl_4.cub"
m19="maps/invalid/nl_5.cub"
m20="maps/invalid/nl_6.cub"
m21="maps/invalid/one_info_missing.cub"
m22="maps/invalid/over_int.cub"
m23="maps/invalid/space_in_colors.cub"
m24="maps/invalid/wrong_order.cub"


printf "\n${P}${FLL}****************${P}${FLL}${RC}\n"
printf "${P}${FLL}${RC}${RB}cub3d MAP TEST${P}${FLL}${RC}\n"
printf "${P}${FLL}****************${P}${FLL}${RC}\n\n"

run_maptest
run_maptest ${m1}
run_maptest ${m2}
run_maptest ${m3}
run_maptest ${m4}
run_maptest ${m5}
run_maptest ${m6}
run_maptest ${m7}
run_maptest ${m8}
run_maptest ${m9}
run_maptest ${m10}
run_maptest ${m11}
run_maptest ${m12}
run_maptest ${m13}
run_maptest ${m14}
run_maptest ${m15}
run_maptest ${m16}
run_maptest ${m17}
run_maptest ${m18}
run_maptest ${m19}
run_maptest ${m20}
run_maptest ${m21}
run_maptest ${m22}
run_maptest ${m23}
run_maptest ${m24}
