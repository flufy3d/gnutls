/*  -*- buffer-read-only: t -*- vi: set ro:
 * 
 * DO NOT EDIT THIS FILE   (ao-strs.c)
 * 
 * It has been AutoGen-ed  May  6, 2012 at 04:20:58 PM by AutoGen 5.16pre36
 * From the definitions    ao-strs.def
 * and the template file   strings
 *
 *  Copyright (C) 2011-2012 Bruce Korb, all rights reserved.
 *  This is free software. It is licensed for use, modification and
 *  redistribution under the terms of the
 *  Modified (3 clause) Berkeley Software Distribution License
 *    <http://www.xfree86.org/3.3.6/COPYRIGHT2.html>
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *  3. Neither the name ``Bruce Korb'' nor the name of any other
 *     contributor may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *  
 *  strings IS PROVIDED BY Bruce Korb ``AS IS'' AND ANY EXPRESS
 *  OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 *  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED.  IN NO EVENT SHALL Bruce Korb OR ANY OTHER CONTRIBUTORS
 *  BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 *  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 *  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 *  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 *  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "ao-strs.h"

char const ao_strs_strtable[6266] =
/*     0 */ " \t\n"
            ":=\0"
/*     6 */ "INVALID-%d\0"
/*    17 */ "*INVALID*\0"
/*    27 */ "none\0"
/*    32 */ " + \0"
/*    36 */ " | \0"
/*    40 */ "%s\n\0"
/*    44 */ "PAGER\0"
/*    50 */ "/tmp/use.%lu\0"
/*    63 */ "more\0"
/*    68 */ "    --* )\n\0"
/*    79 */ "%s\n"
            "  \0"
/*    85 */ "  \0"
/*    88 */ "    -* )\n\0"
/*    98 */ "        ;;\n\n\0"
/*   111 */ "stdout\0"
/*   118 */ "%A %B %e, %Y at %r %Z\0"
/*   140 */ "#! %s\n\0"
/*   147 */ "%s_%s=\0"
/*   154 */ "\n"
            "export %s_%s\n\0"
/*   169 */ "''\0"
/*   172 */ "\\'\0"
/*   175 */ "'%s'\0"
/*   180 */ "%s_%s_%d=\0"
/*   190 */ "\n"
            "export %s_%s_%d\n\0"
/*   208 */ "set --\0"
/*   215 */ " '%s'\0"
/*   221 */ "'\\''\0"
/*   226 */ "\n"
            "OPTION_CT=0\n\0"
/*   240 */ "=%1$lu # 0x%1$lX\n\0"
/*   258 */ "true\0"
/*   263 */ "false\0"
/*   269 */ "VERSION\0"
/*   277 */ "OPT_ARG_NEEDED=OK\0"
/*   295 */ "OPT_ARG_NEEDED=NO\0"
/*   313 */ "OPT_ARG_NEEDED=YES\0"
/*   332 */ "LONGUSAGE\0"
/*   342 */ "flag\0"
/*   347 */ "%s_%s_TEXT='\0"
/*   360 */ "'\n\n\0"
/*   364 */ "option\0"
/*   371 */ "\n"
            "env | grep '^%s_'\n\0"
/*   391 */ " -- %s\0"
/*   398 */ "--\0"
/*   401 */ "\t\t\t\t- \0"
/*   408 */ "\t\t\t\t  \0"
/*   415 */ "\t\0"
/*   417 */ "    * )\n"
            "         OPT_PROCESS=false\n"
            "         ;;\n"
            "    esac\n\0"
/*   474 */ "  %s\n\0"
/*   480 */ "%%-%ds\0"
/*   487 */ "%1$s /tmp/use.%2$lu ; rm -f /tmp/use.%2$lu\0"
/*   530 */ "# # # # # # # # # # -- do not modify this marker --\n"
            "#\n"
            "#  DO NOT EDIT THIS SECTION\n\0"
/*   613 */ "%s OF %s\n"
            "#\n"
            "#  From here to the next `-- do not modify this marker --',\n"
            "#  the text has been generated %s\n\0"
/*   719 */ "#  From the %s option definitions\n"
            "#\n\0"
/*   756 */ "\n"
            "if test -z \"${%1$s_%2$s}\"\n"
            "then\n"
            "  %1$s_%2$s_CT=0\n"
            "else\n"
            "  %1$s_%2$s_CT=1\n"
            "  %1$s_%2$s_1=${%1$s_%2$s}\n"
            "fi\n"
            "export %1$s_%2$s_CT\0"
/*   877 */ "\n"
            "%1$s_%2$s=${%1$s_%2$s-'%3$s'}\n"
            "%1$s_%2$s_set=false\n"
            "export %1$s_%2$s\0"
/*   945 */ "\n"
            "%1$s_%2$s=${%1$s_%2$s}\n"
            "%1$s_%2$s_set=false\n"
            "export %1$s_%2$s\n\0"
/*  1007 */ "\n"
            "OPT_PROCESS=true\n"
            "OPT_ARG=$1\n"
            "while ${OPT_PROCESS} && [ $# -gt 0 ]\n"
            "do\n"
            "    OPT_ELEMENT=''\n"
            "    OPT_ARG_VAL=''\n\n"
            "    case \"${OPT_ARG}\" in\n"
            "    -- )\n"
            "        OPT_PROCESS=false\n"
            "        shift\n"
            "        ;;\n\0"
/*  1201 */ "\n"
            "OPT_ARG=$1\n"
            "while [ $# -gt 0 ]\n"
            "do\n"
            "    OPT_ELEMENT=''\n"
            "    OPT_ARG_VAL=''\n"
            "    OPT_ARG=${1}\n\0"
/*  1291 */ "    if [ -n \"${OPT_ARG_VAL}\" ]\n"
            "    then\n"
            "        eval %1$s_${OPT_NAME}${OPT_ELEMENT}=\"'${OPT_ARG_VAL}'\"\n"
            "        export %1$s_${OPT_NAME}${OPT_ELEMENT}\n"
            "    fi\n"
            "done\n"
            "unset OPT_PROCESS || :\n"
            "unset OPT_ELEMENT || :\n"
            "unset OPT_ARG     || :\n"
            "unset OPT_ARG_NEEDED || :\n"
            "unset OPT_NAME    || :\n"
            "unset OPT_CODE    || :\n"
            "unset OPT_ARG_VAL || :\n"
            "%2$s\0"
/*  1621 */ "\n"
            "# # # # # # # # # #\n"
            "#\n"
            "#  END OF AUTOMATED OPTION PROCESSING\n"
            "#\n"
            "# # # # # # # # # # -- do not modify this marker --\n\0"
/*  1737 */ "        case \"${OPT_CODE}\" in\n\0"
/*  1768 */ "        '%s' | \\\n\0"
/*  1786 */ "        '%s' )\n\0"
/*  1802 */ "        '%c' )\n\0"
/*  1818 */ "            ;;\n\n\0"
/*  1835 */ "        * )\n"
            "            echo Unknown %s: \"${OPT_CODE}\" >&2\n"
            "            echo \"$%s_USAGE_TEXT\"\n"
            "            exit 1\n"
            "            ;;\n"
            "        esac\n\n\0"
/*  1977 */ "            echo \"$%s_%s_TEXT\"\n"
            "            exit 0\n\0"
/*  2028 */ "            echo \"$%s_LONGUSAGE_TEXT\" | ${PAGER-more}\n"
            "            exit 0\n\0"
/*  2102 */ "            %s\n\0"
/*  2118 */ "            if [ $%1$s_%2$s_CT -ge %3$d ] ; then\n"
            "                echo Error:  more than %3$d %2$s options >&2\n"
            "                echo \"$%1$s_USAGE_TEXT\"\n"
            "                exit 1 ; fi\n\0"
/*  2297 */ "            %1$s_%2$s_CT=`expr ${%1$s_%2$s_CT} + 1`\n"
            "            OPT_ELEMENT=\"_${%1$s_%2$s_CT}\"\n"
            "            OPT_NAME='%2$s'\n\0"
/*  2421 */ "            if [ -n \"${%1$s_%2$s}\" ] && ${%1$s_%2$s_set} ; then\n"
            "                echo Error:  duplicate %2$s option >&2\n"
            "                echo \"$%1$s_USAGE_TEXT\"\n"
            "                exit 1 ; fi\n"
            "            %1$s_%2$s_set=true\n"
            "            OPT_NAME='%2$s'\n\0"
/*  2668 */ "            %1$s_%2$s_CT=0\n"
            "            OPT_ELEMENT=''\n"
            "            %1$s_%2$s='%3$s'\n"
            "            export %1$s_%2$s\n"
            "            OPT_NAME='%2$s'\n\0"
/*  2809 */ "            if [ -n \"${%1$s_%2$s}\" ] && ${%1$s_%2$s_set} ; then\n"
            "                echo 'Error:  duplicate %2$s option' >&2\n"
            "                echo \"$%1$s_USAGE_TEXT\"\n"
            "                exit 1 ; fi\n"
            "            %1$s_%2$s_set=true\n"
            "            %1$s_%2$s='%3$s'\n"
            "            export %1$s_%2$s\n"
            "            OPT_NAME='%2$s'\n\0"
/*  3116 */ "            eval %1$s_%2$s${OPT_ELEMENT}=true\n"
            "            export %1$s_%2$s${OPT_ELEMENT}\n"
            "            OPT_ARG_NEEDED=OK\n\0"
/*  3236 */ "            OPT_ARG_NEEDED=YES\n\0"
/*  3268 */ "            eval %1$s_%2$s${OPT_ELEMENT}=true\n"
            "            export %1$s_%2$s${OPT_ELEMENT}\n"
            "            OPT_ARG_NEEDED=NO\n\0"
/*  3388 */ "        OPT_CODE=`echo \"X${OPT_ARG}\"|sed 's/^X-*//'`\n"
            "        shift\n"
            "        OPT_ARG=$1\n"
            "        case \"${OPT_CODE}\" in *=* )\n"
            "            OPT_ARG_VAL=`echo \"${OPT_CODE}\"|sed 's/^[^=]*=//'`\n"
            "            OPT_CODE=`echo \"${OPT_CODE}\"|sed 's/=.*$//'` ;; esac\n\0"
/*  3639 */ "        case \"${OPT_ARG_NEEDED}\" in\n"
            "        NO )\n"
            "            OPT_ARG_VAL=''\n"
            "            ;;\n"
            "        YES )\n"
            "            if [ -z \"${OPT_ARG_VAL}\" ]\n"
            "            then\n"
            "                if [ $# -eq 0 ]\n"
            "                then\n"
            "                    echo No argument provided for ${OPT_NAME} option >&2\n"
            "                    echo \"$%s_USAGE_TEXT\"\n"
            "                    exit 1\n"
            "                fi\n"
            "                OPT_ARG_VAL=${OPT_ARG}\n"
            "                shift\n"
            "                OPT_ARG=$1\n"
            "            fi\n"
            "            ;;\n"
            "        OK )\n"
            "            if [ -z \"${OPT_ARG_VAL}\" ] && [ $# -gt 0 ]\n"
            "            then\n"
            "                case \"${OPT_ARG}\" in -* ) ;; * )\n"
            "                    OPT_ARG_VAL=${OPT_ARG}\n"
            "                    shift\n"
            "                    OPT_ARG=$1 ;; esac\n"
            "            fi\n"
            "            ;;\n"
            "        esac\n\0"
/*  4418 */ "        OPT_CODE=`echo \"X${OPT_ARG}\" | sed 's/X-\\(.\\).*/\\1/'`\n"
            "        OPT_ARG=` echo \"X${OPT_ARG}\" | sed 's/X-.//'`\n\0"
/*  4535 */ "        case \"${OPT_ARG_NEEDED}\" in\n"
            "        NO )\n"
            "            if [ -n \"${OPT_ARG}\" ]\n"
            "            then\n"
            "                OPT_ARG=-${OPT_ARG}\n"
            "            else\n"
            "                shift\n"
            "                OPT_ARG=$1\n"
            "            fi\n"
            "            ;;\n"
            "        YES )\n"
            "            if [ -n \"${OPT_ARG}\" ]\n"
            "            then\n"
            "                OPT_ARG_VAL=${OPT_ARG}\n"
            "            else\n"
            "                if [ $# -eq 0 ]\n"
            "                then\n"
            "                    echo No argument provided for ${OPT_NAME} option >&2\n"
            "                    echo \"$%s_USAGE_TEXT\"\n"
            "                    exit 1\n"
            "                fi\n"
            "                shift\n"
            "                OPT_ARG_VAL=$1\n"
            "            fi\n"
            "            shift\n"
            "            OPT_ARG=$1\n"
            "            ;;\n"
            "        OK )\n"
            "            if [ -n \"${OPT_ARG}\" ]\n"
            "            then\n"
            "                OPT_ARG_VAL=${OPT_ARG}\n"
            "                shift\n"
            "                OPT_ARG=$1\n"
            "            else\n"
            "                shift\n"
            "                if [ $# -gt 0 ]\n"
            "                then\n"
            "                    case \"$1\" in -* ) ;; * )\n"
            "                        OPT_ARG_VAL=$1\n"
            "                        shift ;; esac\n"
            "                    OPT_ARG=$1\n"
            "                fi\n"
            "            fi\n"
            "            ;;\n"
            "        esac\n\0"
/*  5689 */ "%1$s_%2$s=%3$d # 0x%3$X\n"
            "export %1$s_%2$s\n\0"
/*  5731 */ "%1$s_%2$s_CT=%3$d\n"
            "export %1$s_%2$s_CT\n\0"
/*  5770 */ "OPTION_CT=%d\n"
            "export OPTION_CT\n\0"
/*  5801 */ "%1$s_%2$s=%3$s\n"
            "export %1$s_%2$s\n\0"
/*  5834 */ "%1$s_%2$s='%3$s'\n"
            "export %1$s_%2$s\n\0"
/*  5869 */ "%1$s_%2$s_MODE='%3$s'\n"
            "export %1$s_%2$s_MODE\n\0"
/*  5914 */ "echo 'Warning:  Cannot load options files' >&2\0"
/*  5961 */ "echo 'Warning:  Cannot save options files' >&2\0"
/*  6008 */ "echo 'Warning:  Cannot suppress the loading of options files' >&2\0"
/*  6074 */ "%1$s_%2$s_TEXT='no %2$s text'\n\0"
/*  6105 */ "%s WARNING:  cannot save options - \0"
/*  6141 */ "<%s/>\n\0"
/*  6148 */ "<%s>\0"
/*  6153 */ "</%s>\n\0"
/*  6160 */ "<%s type=%s>\0"
/*  6173 */ "<%s type=nested>\n\0"
/*  6191 */ "#x%02X;\0"
/*  6199 */ "<%1$s type=boolean>%2$s</%1$s>\n\0"
/*  6231 */ "<%1$s type=integer>0x%2$lX</%1$s>\n";

/* end of ao-strs.c */
