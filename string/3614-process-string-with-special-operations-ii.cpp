// https://leetcode.com/problems/process-string-with-special-operations-ii

#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    char processStr(string input, long long k) {
        size_t length = 0;
        for (char ch : input) {
            switch (ch) {
                case '*': length = max(length, 1uz) - 1; break;
                case '#': length *= 2; break;
                case '%': break;
                default: length += 1;
            }
        }

        if (k >= length) return '.';

        for (int i = input.length() - 1;; --i) {
            char ch = input[i];
            switch(ch) {
                case '*': ++length; break;
                case '#': length /= 2; k %= length; break;
                case '%': k = length - 1 - k; break;
                default: {
                    --length;
                    if(k == length) return ch;
                    break;
                }
            }
        }
    }
};

#include <vector>
#include <iostream>

vector<tuple<string, long long, char>> test_cases = {
	{ "a#b%*", 1, 'a' },
    { "cd%#*#", 3, 'd' },
    { "z*#", 0, '.' },
    { "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa#############################", 1, 'a' },
    { "%edx#n#lkc####uom##qg#%#b#ek%##%%ocr#m%#fv%i%%#n#u%%#n#q%v#rwvd##t###%#%%%o*"
        "##r#gr*gz#dm%ez", 1, 'd' },
    { "##%##*js%#qxk%oe%tas#n%%%#x*%j#%#h%%######*bxp#p##i%u%%q#o#n#%*ca%#g#hjbz#d%"
        "%k%x%#%#y%*gw%q#f#%q*v#%koe%j%k#n#y#%#sm#et%jyo%#i*h#u##a%%i##%o#rd#j###xj"
        "%#h#%hn#%igde#nyt##bkgf%iuy%%%svgintn%w%q%%q%%%%s%*r%m%%mck%vkceo*%hk%%f%%"
        "fkak%fho%*y*%%%%h%rgomby%l*%%%lbwn%qc%%*%%pp%*%pu**u*%%vwqb%%vzsjh%eb*%%%%"
        "%vnm%zg%j*ouu%i%g%z%%m%%a*o%qxdj%%%%rl*bgxjefpg%%%%%y%t%*%vgsc*dl%%%nw*rq%"
        "c%hyk*ujru%%c%p%%a%a%%%%ii*%iq*%m%noajr%xbp%%i%*%q%po*e%qd%c*%ffkfk%lo%%%x"
        "*%%h*gr%%e*%sj%**h%lev%tl**%t%sl%oli%n*%%dgah", 401973009142641, 'k' },
    { "#g#f##w%v#%p#*#usm%####g#%v#*#vjh#ti##w%%j%zb#j#l%%##e#*qjbnv*%tk%#ryxr##wmv"
        "x#xzjd%oo%%#%bd%n#u##mqp%hs%yr#d##g%#s#####b*tp#f##td%o%#d%#y#g#*ssh#%#ma%"
        "#*j*%%*%%%%m%x%ctl%%%a%xbp%z%k%%e%%cuwhjfg%y%g%rcjp%%ef%xy*bc%%t%%a*mi*f%t"
        "ysu%%%%%w*lbnf%%i%%srqe*%hn*nc%%fx%%%%qt%k%a%wp%*c%qi%vuy%uln%%iry%uyjx%dl"
        "t*f%d%%%h%k%p%cjtyqz%%%%gcng%wn%%*ukks%b%h*usx%%g%x**blv%%*z*c*k%%ek%%*ggg"
        "%%*yo*s%*%***%sm%ypbabrbt%%j%myoj%c*%ijm%%xg%%dxc%k%%ek%*mfyzo%k*fe%*%%%w%"
        "%%wmw%g%%wk%*t%ovt%fk%ub%ep%*%%*%ujmeiksn%%*a*ggxlz%%%*v%%%%%sb%cn%v%f%hjm"
        "*%*ydg%%*%n%k%ag%%%%*mvlge%e*%efvb%c%lx%%%u%*%%%kg%%u%%%%g*f%%k%%%%bw%a%nw"
        "%zkyj%q*r%xjdlnh%o%%n%q*crt%siuo%hrt%%%cyb%w%jn%lsouevo*t%fr%dj%u*jyqim%%%"
        "why%%rau%s%uutq%k%w**jngiw%y*x%%%%%%kt*e*%%fkodk%%d%*x%qti%%%*%q%*%%qp%%sx"
        "%cr%mtjb%%v%yv%*x%ygr%%iu%%%%s*%%e%%srvt%%*%v%lm%l%%s%l%q%cvy%mv%%oe*g%x%%"
        "*qck%*h%a%*%c**%%bppb%*gg%%wkc%zv%%a%h*hg%%%%xq*%kbdj%nw*wg%%%%v%r%%z*n%%g"
        "y*%*%mgm*bb%wb%b%s*s%v%xt%sj%o%%zhh%%rvlys*%*hg**c%%a*%%*cw*wpj*%%o%r%mdo%"
        "gj%ci%%%c%wgj%%*ro%ag%mc%%%%%%*v%%rnj**j%u%x%zyvctg%%%%k%nt%v%n*kvf*n%vphs"
        "y*%%k%g%rz%%*%%%zxbu*%%%a%b%*%%e%s%%dj%%xdc%d%%d%v%%%%g%*e**%%%uxf%jt*%xx%"
        "*%*%%%%ow%%fby%%n%kqr%f%%%%rf%a%b%u%xwio%xmvt%ttp%fzo%l%%*%%wjh%%c%o%r%%a%"
        "rqyc**%ogmaka*z%g%*o%h*%lsq%t%%j%arg%m%%%%p%%fff%z%d%%j%*%evnho%*nr%esog%%"
        "qp%*%zy%%*%v%%%%%%g%%%%*rlyn%%%qgmc%ht%e%%aop%*n%%ztz%%a%%%%m%%g%*%%pf**ym"
        "%bbly%y%z%%q*%h*oqj%%%m%kq%%iair%ih*h%%q%%%%ih%%%nn%%o%%*tgxlh%r%t%%%*%*%*"
        "y%%*hb%d%jvsj%mm%%ri%%r%u%%g%v*don%g%**h%fdf%*w*dtkpf%ibpp%%%qq*f%%%wjha%%"
        "w*%eapay*k%b*%q%o*%%%%%**%c%uq%%hyx%q***%*mbsvg%%**t*lorypqq%xf%x%pgvc%v%%"
        "%g%k*lumx*%o%%%%%%ygtnnwh*q%qd%rtwa%%%facf%*adu%u%*%%v%rn%y*u%%%%s%z%*c%ec"
        "%*a*%%%d*%sc%b%g**t%y%%e%vd%%%s%f%y%mr*m%%%q**jwre%*%%%q%ba%%yss%g%xz%%%rc"
        "%%*q%m%lm%mt%zz%qa*ul*sra%%%%o%b%xe%a*sqztdfp%eu%%f%%%%%mr%%zq%rw%d%r%jw*r"
        "%%%*%m%x%*%lr*%ial%%iqq%%p%%k%ljei%%he***kg%%t%dwhjcepbh%%gqnpg%t%%xhi%%y%"
        "cv%%%*m%%%*i%%%%nkfb%%d%%%%ooh%d%%m%v%%jz%%%%%%%*kl*a%%%fsha*elfs*%sqzv%il"
        "h%*%%h%qh%lc%y%vvq%%%%%%fvp%%p%l*%k%%a%j%h%mkjro%r%%mstcdzlblkn**vkwhn*r%%"
        "%%hxr%ic*sf*vlcn%%ndf*ac%%ag%%pad*j%ai%%%w*f%r***m%icxertp*ojh*%yjb%i%*v%l"
        "%%*%%zw%fv*%cakvxx%%%%%%hktp%%b*%%%z%%p%m%vb%wi%%i%erwhgk%riot%phoi%%*jak%"
        "guxyb*%%%w*%z%ty*tq%es%*%*ogsc%%e%%b%x*y%u*%zbvk%%*d%%%ba%wlf%qw%t*%g%a%%l"
        "%%%k%%n%p*ior%%%%%g%%rql%%difi%*%t%*la%%rdn%x%%%sral*ue%p%%%k%gl%ebg*ip%%m"
        "r%%%ymddfz%uggcssh%%t%mbca%bp%a%%%pi%xgo*rfmjmqynh%as%k%%j*f%ch%i%ld**wbfs"
        "mp%tligotypg%*hhh%%%%*i*x%*%gb%o%*%%%l%n%%%r%%ggt*%epe%l%w%%ia*%%*la%%pe%x"
        "aqq%gxla%r%z%%%k*%o%ax%%%x*%%po%%g**r*r%zwor%mbe%%%d%%a*%%*%ewg%%oq%fd%mlx"
        "%%%b%j%%tz%%%ms%h%i%olj*v%%i%%zhq%k%b****%%x%%y*t*%v%%c%muqj%u%%vo%%%%%ym%"
        "%g*%ts%oa%%l**%%%t%%yibslkpu**dh%%e*e*%%f%i%%%mma%%tn%%y%*%%c%%yd**%**%yj*"
        "oqc*%%w%hfn*osep**ma%*%*gxnbk%z%%%bh*ym*fpx%v*%upu%u*%z%%a%t*o%%s*h%%lw*vs"
        "*%r*%%*%z**x%m%*uobl%agwr%fb%%*%%megom%%bmro%om%y%s%%%*qe*uw%j%%f%*y*p*bb%"
        "%b%i%%jbcvp%*%%%%**mmisxbkl%*z%%%p%o%prv%*%p%vc%ou*%%t%%%i*%%plw**dc%%%e%%"
        "%%df%uyu*d*%*%%%n%iw%lr%**dszpf*nja*c*c%%n%%%%ipr%bekvqy%m*%%%qq*%*%dew%ya"
        "%%%%zu%%c%nz%h%h%%%tdrwin%*x%d%iee%x%*bcn%h*%q%%h%e%a*%%ggz%w%gd%%%%p%%e%l"
        "cpgybo%cr%gvfkks%u%%tlb%%%n*%ka%%%xy*l%i%fd%j*w%f%%%b%%%wlhciq*%%m**y%%x*q"
        "ao%nxj%ql%z%%v%d*%eru%e*vce%l%%b%m%%myioxqa*%xs%%%nk%%%%iq%%%yj%vya%%%%yim"
        "ith%l%lg%sao%%l%qz%z%h%t%*w%%%%%%%%keu*%rk%*m%gow%%%o%**v%*%i%rpbgdsv*kihd"
        "%%k%z%%j*p*%%xkez%%%o%x*%i%v%%uj%d%i*%%t%u*%%guvvvfr%fo%m%%n%%g%nps*z*e*u%"
        "q*%%%jd%kbcb%k*ouy%x%ip%yq%%*pu%%*x%e%%%%o%vkj%qmd%%*%%rmm%txa%*%%%%f%*%%o"
        "%qgl%%%%%%f%%*%joxwp%rcj%%ypr*%yldz%%w%a%%zy*wq*y*o*%%*%%%%%%%x%belq%%*fa%"
        "%a*sx%i*%mtsahi%%ln%d%*l%%rzw*xl*l%u%%%*%tkb%%%vr*%s%%h*u%*%%k%*ijg%%l%wtl"
        "j*%yjtg%uy%l%*%*lki%k%%%hbdwtkta%xliu*vf*%drg%apafrc*met%%j%%m%%kh%%%ovvl%"
        "e%%%k%%%%g%j%kxzq%*hnirz%p%f%%c*rau%%sb%%o%%ra%inc%xf%j%%ib%%tq%%%yrez%*%%"
        "*%vgshr%%%%%%y*mny%*ug%%%uxgz%i%za*%%%*%x%xjb*%**%ob%%%%%%*y%w%%i%%uo*%%do"
        "%*%%nobht%%%%ii%g%npq%%%elex%%%*u%%o%%%u%%%%xs%%j%*fm*kd*z%*%%%xa*%e%qplig"
        "%%*%h%g%tskjdv%%%ied%wnv%ir*z%%%kujmmd%c*%%%d%%y*nzj%%yu%%j*md*y%u*u*%qal%"
        "*%e%%%***%%t%rqd%%%glsoxn%fppd%wz%%z%t%s*%%%g*b%qbwycvvr%%%*%g%t%*y%%%e%%i"
        "%coh%us%xc%%%ziglutuk*%%%uk*%j*%u%xr*%%%*p%o%n%zcxq%%p%lr*w**%%%a%q%%%%%h%"
        "%%%y%zx%%%e%%%i%%%ghr*u%vndv%%j%sp**xe%todetvl*m%%wom%v%%%ty*%qwr%mb%%*q%%"
        "o%%gam%mbxya*g%%%judr%qtac%%afvj%d%%%%%a*q%%%*%id%u%*tq%*%r%h*ysol%h*%o%%%"
        "qv%n%%%%ze%z%*%%%i%%uxf%pnv*fna%%zheb%%pk%%hlxyapqv%ab%*%%ezn%a%rn*%i%%%kg"
        "qwym%g%vj%b*sn%%xfc%jcrs%%t%hs*x%erud%*v%%rivrka%*wf%%%hmxk%usb%afu%f%%w%%"
        "%py%yjon%%vwil%o%l%%%zpv%%*xh%%n*%tvg*%%*%x**t%*l%%eqv**%%%%%a%*m%%%adp%*%"
        "zyq%y*f%*%e%%cv*%p%vna%eaknyz%%%%%q%fe%%fq%%%%xwu%*%f*b*%jt%%n%%%rzpcgk%i%"
        "d%%ftul%%%%vyu%pl%u*%%xh%%%d%%gv%by%%lz%%q%%%am*l%%o%%k%*%ap%%b%b*%b*%t%r%"
        "%y%u%%y%*%%nml%%d%*%t*%wud%e%%%fl%%%%yp%n%*el%rb%*%*%g%oxbpannc%%%au%%%%m%"
        "fxhe**q*%p%*%%f%%weq%%jrl*%%%*h%e%%ufam%%*eish%%tuxtl%q%l%*%%%*l%%%*%%okc%"
        "%bo%%km%slyc*f%ms%%l%%%*fo%fup%%z**%rn%%ko%y%r*r%ve%iii%%hv%e%o%%*k%ir*vd%"
        "os%%a%%zt%uit*de%%%m%s%kn*%ap%z*eggja%u%iekcep%cb*%aw%w%*jky*i%%m%trzr%%b%"
        "cqym%%%k*v%%rkl%%*z%*t%%%sf%xj%ik%bxbp%%kn*odds%i%ihz%yknevbci%h%oh%*kqn%x"
        "f%u*%%%fre%%i%%u%do*%%*%ximp*o%z%qjy*%%*o*%l*%*i%wkuhq%q%xcysi%frfb%*ykhmy"
        "%%bvqbp%ay*vnj%%a%%ku%*tygk%*eu%jjxcyx%%b%x%%%p%k%%%%ak*n*i%q*x%%%bj%%yr%*"
        "uo%tzk%%%%%hwxnq*e%%edgu%pz%eobv%t%%%ka%ko%*%*%%%%rb%r%%*sns*%%c%s%%x%x*%r"
        "dajxz%*d%%l%%%e%y%%%oer%uq%%%o%mprk*%*l%i%%*i*%%%%skp%*yh%%ryt*%uum%pbkugo"
        "ys*%%%ahi%%jki%%*%efr%h%%fb%%g%%%%rn%mvjy%%u%f%%%*mhju%l%j%%%%ltvgz%*%*bl*"
        "%v%ul%wag%k%sn*%sgp*%%%d%%%%%go%ypc%t%%o*werlt*l%mg%%%%oq%p%a*exj%bq%nl*%l"
        "ccbi%mq*u%%g*jdp%viwxux*pysm%%j%%dpg%%%%z%%iwnyn*%xqc%%*a%au%%%cnh%%ht*o%%"
        "*n%*%ejf%r%t%%%scxb%**%jw%%uk%weyx%%%higr%l%g%qc*%%%%%z%xiu%xw**r%g%jdh%**"
        "h%%f%o%%%**o%%p**e%yd%%q%%a%%nl%%zsp%%v*%%%l*%vxcyve%k%a%m%%zne*m%a%em%ro%"
        "**w%j**ap%*kebm%*%f%yus%v%%%%l%*z*%cbuyjq%%ng%tsfec%%x%%zr%e%%%%%kniz%vb%%"
        "fpv%t%%z*%vudjngi%y%*elsjxr%hnf%%cip%k*a%e%d%*dau%zew%myr%gh%*q%ii%p%%m%um"
        "zr%%n*%k%wj%*zgxq%%g%i%q%%%tyx%%%abrpuqn%%%%*g%%%%lbia%%%ww%%d%gs%%ccehf%*"
        "vh%rh*e%dr%%%yj%n%%bv*uq%o*v%%mq%%%*%xemz%k%i%**jc%lw%s%q%*oh%%b%%%%*l%pgu"
        "*%hj%%z%g%%%*e%kemvodxu%g%%a%%cqa%u%fcdjw%**b%%%%%jhftp*v%gwjw%hbsbnvyf%j%"
        "xt%cv%i%veqd%c%jb%a%arpjo%*t%f*w%l%%f%tcbc%%*z%%rq%**%%w%%bj%sex*g%*at%p%d"
        "ut%*%w%%kn%%trc%fg%%%%%%a%%*%fhy*%sj%%ookozguu%sg%%u%%%*%%yr%%*mb%%*%j%vo%"
        "w%%%%%*f%ayu%*%%%v%sn%v%db%kat%*h%%s%%%oj*%%f%qaiax%mlszoysd%w%fnr%%*%nng%"
        "wi%rqalwe%%t%z%%p%ow*%lt%%cyw%gpnk%t**%*%%o*%*bw%i%w%%zzpv%qe%xr%k%oduutw%"
        "m*f*yj%%a%x%*r*%fb%c%hvyq%%tt%u%%gjfx%%g%%z%yw%*n%u%jmf%g%z%%r%w%zl*%%hm*%"
        "tqmhfaw%%yp%%upzw*awp%f%a%%%g%tew%*%**%slhir**%l%kf%px%x*%%n%oezeq%yqi%dl%"
        "hls%vr%*%%f%hc%fh%%pr%ihshk%%*%s%zd%y%%b%k*ma%%%%*sr**fo%%et%xvp*h%%%%%%%x"
        "b%%cqp%o%*w%**%vdgpy%c%%a%%%ix%%*%yjp*b*%%ysq%%eptgy%%%%*x**aow%xjr**y%nf%"
        "u%t%%iibd%%*snbap%am%%%%hn%n*%%s%v%%%*u*ip%e%w%%*%*%eue%uy*%z*x%*ch%%vw%*%"
        "*o%cs%%g%%q%ipz%*%%cuoe%%*%x%j*je%%*hzs%ng%%%rgj%ubh*%%ob%%u%kr%%*v%ymix%f"
        "%bbi%%vn%%p%%*uvg%%q%%kwx***hf%p%e%fx*%jl%%t%r%e%%%%%*%o%up%*s*%%wje%zb%q%"
        "*lq%q*tqto%%%%%w%%*%b%%%t*y%*g%pd%%*f%**z%*%%hw%p%%%%%vy*ykk%%%x%ftp%*%*%*"
        "q%y%suuc%%%%ga%%%%c%m%*d%%%%veko%%ud%%v%m%%%*svy%%i%n%jj%%rpvk%%*catn*m*b*"
        "*%%rigv*cgrqh%%%%%x%uu%zf*%%u%%*t%h%lbk%y**yx%*ibw%lo%*d%%ltubr%%**zt%skg%"
        "%v%*en**xba%sl*c%br%%ws*ufcmxug*a%%ywe%e*vj%*s*zg%z*fqu%%nu%hqf*rqa%%w*%af"
        "w%%dq%h%h%m%wfl%%i%%*%%ug%%%%bjr%pqg%%v%wc%%**%q%z%*g*s*%tf*%srrof%%%%%mb%"
        "*%%%wt%%h%%*%*k%prwx%%ijhf%p*gni*%s%wq%%*xu%*u%ke%krk%%*it*ft%v%r%w%ne%ikx"
        "**a%e%p%%w%%nl%%%%eagf%%%*k%%v%%%wt%gj%l%%yy%%jl%%hpb*%r%%xjmg%v*zc%sa%v%%"
        "%%%*zk*%wxikacsh%%%u%%b*f*%f%*%pbogvb%**%w%**n%sp*ma%pb%%%o%%*%%jxo%jqrpc%"
        "u%%zv%m**%%h%%m%n**%%%%j%grta%cu%aja%g%tzg%%fs%gydf%%g*rw%w%ri%%%nia%%kddw"
        "%b%d%o%q%%av%kqf%*%bgp**e*r%x%%c%s%%%rp%n%yt%%%em*%%hm%rik%%%%dha%%%p%%p%k"
        "t%%%%%tduw%%%t%%%*%%*%%e%g%%*%%*g*anp%so**%%oz%xv%g%*%j*fgxyn%lyunvqc%dikm"
        "j%*zk%%*%na*%t%m*y*%%wv%v*%tlv%e%%is%nzv%p*banqy%pwzh%e%il%%%zn%rks%s%%i%w"
        "h%%slz%i*f**a%%aitfhy*%%%%%%%*%nto%%%%%yd%bs%*j%yjr%z%c*%qa*%h%g%%%qfwjtra"
        "zpd%%%*%*y*jra%%x*bzlp%%sg%i%u**%%nop%irx*dbn%%r%o%%yhrmp%d%%fee%%%%%%wl%%"
        "%*%dnlp%*%%j%c%%%dau*x%l*r*t%kw*k%%%z%*%%*g*%y%%j%%%c*e%%%%*h%%k%%s%upq%x%"
        "%wpk*y%*mg%%dlq*%%pu*%%tw%%diiyt%c%uo%*%x%q*c*lh%mhzhu%%%%b%t%%%%%%*iimo*%"
        "i%%*jonp%jqn*nxr%l%%e*%%%%%s*%*%q%gb*%hwo%%nh%y%%s%x%rrw%x%*s%%x%n**v*s%%n"
        "%dc*n**%%i%%t%%uf%y%ih*k%nuaj%jmxu%e*%ob*jt%%uez*ec%%%z%%a%mj%%%%%%ftopwd%"
        "h%%g%pe%*%*%idrrs%ed%%x%%ljzve%d%ykx%k***%lx%k%c%%ie%%%q%l%*%h%b*%%xt%o%%l"
        "*w%u%nde%u**p*%%sd*m%%dkw*f%%%e%%b%pf*%vu%%xz**u%%el%%%ouj*z%g%m%jte%nk%*%"
        "kdd%**kbm%*pp*ohxd%nq%%%ot%hmv%%vdl%*p*%h**wob%xd%i%w%i%%ojwu%%vv%%l%w%q%w"
        "ipjnxrmm%%n%swxxupb%t", 19255508, 'g' },
    { "%u%#ye##ouezo#%jw%n*#%%p*##%oo%z#h#y##%#t#w%v##%n#e###%y#w%#%%#a%f#%a*bl#ttu"
        "###vhuu###kyi%q##br#%#j#g*g##febnkdpn*k##l##xjd#ukog####%wv%#nqb*%t#t%eg*%"
        "lmlqkzdqa%%nebnjml%%o%n%oal%%%%i%b%xzvuh%g%p*%%u%%l%%b%wih%%o%%pgxyl%%%gim"
        "*%%%*wj*ee*%rievg%%%v%by%y*%%u%%%w%w%f%*%%ensg%%o*%p%%c%ouj**i%xl%x%f%*vdk"
        "%e*%h%h%%lk%od**op%yt**%%%%%rjuk%k%%u%%jgz*%y*s*%rty*%*vtx%*mi%t%ilvwa%nk*"
        "%*%fxm%x*zie%aac*ya%*%*%bujp%avivyw%*%%g%v%js*%t%%sr%im%%%o%ro%%rk%w%sa%f%"
        "%%%%rwgl%a%%%%w%%dx%p%%b%rvopx%je%o%i%sjg%v%*%j%%mk%%%%p%sb%%*f%*%%c%%%%tj"
        "%jt%z*s%oy%n%c%buuz%s%pg%%l*jj%%%v%v%%aqrhosv%%%i%dw%cku%p*svyyrkc%%l%%x*d"
        "%zleeu%%kq%*rpe%ne%%apg**%*%%*%*%sz%h*%nw*yybj%q%x%h%%*w%%%qobsc%%%v*d%m%*"
        "k%jth%a%%k%mcy%pv%%%%%nz%*%r%x%up%**o%%**uaoi%zcfb%fy%lg%*%%mnk%%%%zenvl%n"
        "rn%oil%%%%%o%y%pyw*mqq%*x%c%%%%*zy%k%%c*y%*k%c%%wvz%%vcewtj%we%p%%g%b*t%wj"
        "gq%%%yaqilxm%qxzj%ukg%y**%el%r%%%za%*%gb%x%da%bmvxj%r*%r%c%lh%inq%cs%immci"
        "akem%*ng%%%*%q%j%kuavd%d%*l%o%x%%i%m%x%*%%l%*%r%*c*%o%%*w%ugavin%%%*%%kiza"
        "p*my%c%eoo%%qc%ec%yrjk%%b%e*nld%%%pzvca%*x%rxat%%*%u%*%%ey%m%*%%h%%nd%d%%%"
        "hshr%*ww*nw%m*%%qncpe%c*v*%%%%lcf%f%*%%%d%va%ef%%ly%*%pwvvwg%x%ib*%s%uk%o*"
        "oh%%%s%x*ryjc*jhalv%%y*%%wi%wbzo%ot*x%%rik%tog%c%%%b%%%i%gvrn%*jpq%%%%%%%*"
        "%u%%k%%d%%yk%h*gxg*%q*%q%%b%w*e%%g%b%m*%z%i*u%dg%*vm%%***%i%*rz*c%*q%g%%zw"
        "%%*aalo%fakssbfsut%rzs%i%%r%lmh%g%x%bu%%%s%%j%%z%udtpq*l%%j%*%emb*q%%cs%*z"
        "%i%%yf%%%j%%%k*%koub*%rdd%%lrgd*dvs**%*s%f%*mc*fuq%*o%%*t*%w%mik%wl%*n%y%%"
        "%c*%bstk*%%g%me%%%%fr*qfg%%vtts%sf%*nhvcys%*n%y%*%fer%ytnwnap*%i%%%%v%l%h%"
        "%%sq%sj%*b%%lr%zn%a*%nq%p%%%%ioh%%v**v%s%%c*p*uzcfz%%ft%%wv%%*%%j*u%b%%yif"
        "m*iszn%*%%%%zy%s%**uec%%%sjn%uoc%lwmca%e%h%di%lq%%no*%%%%%h%%%n%%%upb%x%d%"
        "lmr%g%*%%q**juq%bcggaq%%%x%*%g%vd%%*gk*y%ce%m%%%%%a%*z%*x%%%%**vqmno%s%y%u"
        "%f%avsh*%%*f%pa%vw%%%i%dsqvb%*r%i%%%%%%%kamc*%%ua%s%%%s%%%%w%py%o%*cs%%%o%"
        "hlkq%k*b%v%mkry%%nxz%%%ze%%r%%nn%ne%%w**va*z%%%a*ih%ll%%%p%tm%dk%m%k%x*%r%"
        "*k*zi%*r%%%x*v%eciker%o%*%ezk%%b%%%w%%y%yoo%thjlm%*%w%%%cm%ln*uf*%%q*%w%e%"
        "%m*%%%g%ipwl%%*v%%%g%%z*e%*v%%%*%r%%%rnv*%mh%%q%auzw%%%%k%%%sl%%tkuiwa%b%%"
        "%%tffs%*fd%hy%klm%%*%***lthmrr%d*%l%bkpksy%lc%t%z%%%%ehc%%%y%m%%%%iw%%%uf*"
        "x%t%l%pze%t%m*u%x%xq%e%pfxd*d%%w%stjt%qvji%unjes%nhs%itrh%oa%%%w%**r%%%k%a"
        "%%czg%*be%%%%%*ts%sjt%wxrn%%%d%rve%%hilz%%%%%t%twwbled%xn*%%*%ke%%**w%w%h%"
        "%*j%%%km%%wj*%***%*x%%g%no%shi%%%b%%wx%%cxxrdc%ua%%%%%qm%z%%%%%%%%*zb%af%%"
        "*%%t%%%sq%%g%mejs*%f%%%%%c%%pku%%%%*%y%**j%%b%crt%v%mrs*%h%%q*n*%l*ad%u%tm"
        "d*%%%t%jij%g%%*%je%ru%xl%*a%%%%vr%%%l%%n%n%*%k%*%s*%ulkg%u%%i*kafqhdnys%t%"
        "bfws*%%thjd%*%*oi%%rn%w%pz%a%%%y%%x%%y%ek%%*a%hm%vdx%hib%f%%az%*%%t%a*%*%g"
        "%*%**%om%%skwz%emk%%f%%%iy%q%b*%u%%gm*j%%%%%yt%b%x%%%%z%y%na%%a%yuzv%%%ian"
        "fyfn%dv%v%u*f%%q%ldul%%%d%*i%%%%*%u%d*%%jal%%*zg%ir**%w%b%%p%hjg%a*%%%%q%d"
        "%sa%**%%%%ncd**d%%%l*miu%%x*%*%%nh%e%**punge%gglfbne%hj%%a%h*%b%pijj*%ry%k"
        "%g%%%%%u*i%%%u%%*%%u%%g%pet%%s%**c%%hap%a%%%x%m%%%n%re%%s%%%%%%sn%%%mud%%u"
        "*o%%%%er%y%razs%k%*%%%e%%a%%%pz%q%mirv%%lf%%%uf%%%w***%w%wuc%*y%%%jrn*%%%v"
        "*%%f%m%%emwh**i%%w%w%ngo*%vp%%ol%*%e%%t%%vc%%%k%i%*qoy%d%xw%%sxf%%%oe%%%%%"
        "iu%vs%%vhv%j%%l%%%eb%%%diex%%ubj%ivt%mv%h%m%%bh%***qhi%ghfpr%%*ds%%w%%%at%"
        "%xbppa*n%f%*oe**%fa%%%%%k%*j%whm*j%isllq*%%jwe%%%bho*%ym%aja%%xbb%%*f%%biz"
        "%*i**%%a*%%s%n%%yqrs%%%dxwk%%n%*%il%%c%y%%*uk%%%rcfs%qt%%%af%*%%*db%g%%yef"
        "nhb%ll%%%wrayvo%%%%hsqf%%kx%qinhft%%xwx%n%%ql%%%s*%%%%*%%s%qljkf%%*gmzee*r"
        "p%%l%*kh%u%a%%*i%jtqu%p%%%a%%gar%fx%%%b%%k%tky%z%*y%fa%%o%%%rf%sb%vl%%%%pl"
        "ntyd%dkr%r%%%jc%*gwuv%%bhx%%%d*d*%pe%%w%%vkpk%%f%%yt%%**%u%*%i%%*lmewkpz%%"
        "qjt%%dm%l%e%n%yy*k%**%gr%c%m**g*%%*g%e%*%%*on%%*oy*ld%i%%%%%rbw%or%%*%%%t*"
        "u%t%w%%%i%%g%%%rxy%a%%*w%bt%tj%mn*s%da%%im%*%d*qnc*%tywv%io%%%x%*tvr%v%*%%"
        "w%m%%*j*poi%%nwqxb*%%*wd%%y%ihl%y%%%b%aj%qfu%%*%%iyvlv%%cwz*%tqj%cyeyvh%h%"
        "%tx*%%%euo%%e%%%*%l%l%%%%%c%%s*%r%*%*b%%zs%%%*hb**ssjsa%ucoyfm%mr%i%%%h%%%"
        "%w%a%vqtp%zsl%kv%s%sut**t%elnh%%e%%%%kc*%*%%%%p%uk*p%d%hi%pa*ulym*%pxvi*%*"
        "%%g%*%*%%bap*yue%%gcna*f%h%%b*qf%%%qm%%%%%ws%bfj%**%no%%s%%s%ms*%ggd%%nao*"
        "%%%%%%c%*kq%l*%y*%%*%q%%hu*%p%*n%dj%%p%s%%n%%%w%rh%%e%a%*eow*%%%x*%*t%%mzw"
        "%u%zohd%**%%*as*q%%u%*%d%%moypsgt%%%dmzovkwl%p%%*%%h%d*ig%*p%g%%gl%s%%c%%z"
        "%h*tin%%%%%ou*nasa*%n%*s%cv*%awnv*mkm%cuu%%%*%q%bogr*%%*at*e%w%*kblh%mqpni"
        "e%q*%%j%%%%j%*d*ge%*%%%edkuv%%l%lr%mphs%ht%ea%%%g%lxkmgeqfo%*vkm%l%%bw%d%%"
        "%ja*ta%rok%%zkr%%%lthzub%%nr%%%%o%%%%ykw*%%*%ib%%sb%fbkh%x%%*%s%y%%hpxz*l%"
        "h%s%%%*q%iz%%%kxmk*%e*kq%h%%%sib%c%%vaz%%ogrvtrjo%*dr%ep%u%hp%mbm%aw%%%q%h"
        "%d*%cbrk%n%qnlc%xc%%%%qh*fc%zei%%v*mfxq%t%**%c%zw%%%%hpu%%r%%%r%wxy*j%%%*q"
        "n%%%%jul%k*%%jc*a%%xewh%%%*e%rpuz%nz%*k%%de%b%%%%%gw**%ehbz%y%a%x%w%*w%%%o"
        "%bu%*cm**s%ed%p%%y%%ex%v%%%x%%hkgk%u%%%%i%%*%%%xgbjh%%*f%xco%ig%z%%%rgp%%%"
        "%%e**w%**%%z%t%%o%zqte*%%ek%%qzj%as%heyxx%ic%%%%d%*bfpavj%d%kwxub%d*twxa%p"
        "fz**%%%ko%l%%%%%ee%ha%%%g%a*%qq%rnew%%%%%*xgya*%the%p%%quz*j*z%%%%d%*v*f%h"
        "%*g%%pkwd%e*%*%%uiw*ocu%*gw%%xug%x%*%y%f%%xf%%lda%%%%zg*%%a%e%q*%%sc%sm%sj"
        "%e*%%hm%%m%%*haf**%k%h%%%%qt%%wtdd*gxib%%%*rb%u%vlurgdi%%ylz%g*%*%%%*d*%*q"
        "%db%%%iwfq%eshajve%l%%%%d%%m*v%v%w*x%%b%%e%%r%%o%%tz*%f%%*vv*%%%%*ytv%sb%*"
        "%l%v%*di%%t%gtdbfd%k%%%%*m%b%e*ls*h%k%%y*vr%%brj**fv%%uhgq%*vm%hubkyvzsn%v"
        "%rci%**veu%nv*onx%s%g%ojw**%%%f%z%%x*x*%*qo*dl%%%gjrc%%%myol%pguf%%m*%%**i"
        "tk%%sd%%*%%wxl%%hgfmek%uyn%%%%%%%%%s%v%wnku%%%c**%krq**%%**smpn*%%mr*b*hm*"
        "%w%%%w*x%lu%*x%%ra%%y%*y*s%pqn%%bzlne%puxhx%ftloz%%%%**%*mjkq%opna%mm%%%%t"
        "nwq%*%%j%*ktaytkc%%whiq%%%%gddood%*d%%*w%%qngl%u*%%x%aj%%%%%%*i%%%a*brjyy*"
        "n%j*%*u%%jpi%%%g%ig*uog%p%%%*b%syx%*qh%%cuta%oxs%z%xu%%%%j%fv%%l%u%qe%zy%x"
        "tta%%as%hy%wuvn%%%w%l%h*%%%to%p%dhbfykmc%%%%*pxa%w%y%%*cq%tj%jmih*%*nzm%%x"
        "qu%%lth*kqqhb%%*%%n%ml%x%lhh%fpx%m%%cz%p%hpw*zj%%xm%s%*x%**%fu*%%%nxd*e%*p"
        "ibjg%mw%*%%b%jl*a%a%%l%%%%%k%%%t%qs%*%*a%kh*t%%ng***p%*wwgepttc*%ku%b*z%%s"
        "e%%l%leku%%%p%%%hr%sm%%%*b*k%%%owt%%j%*%%p%z%%n%d%l%%qo*%%%jp%%%%%b%my%%%k"
        "y%hmrj%%%%%%s%%ywva*%%%%to%%*%f%%ix%*%*%bag%%n%qwtdwz*%ov%bq%%u%vre%%jmmc%"
        "y%%cc*v%*fz%jv%y%puum%%%x%*xln*c%%**z%*%g%%%%kz*%%fe*km%ozig*%%g%%wd%%*%%%"
        "%jz%*qrt*yayzp%sx%ftfj%%%%%b%%lhi%bi%n%haxzgrjgj%*ajs%z%xy%*k*%x*%d%m%*b%*"
        "y%kwv%%%%qonudli*it%*%%gbr%l%%qj%%*%qqs%%%n%%y%rbe%%*%oa%*%%i*m%%%lutz*%*%"
        "%mv%pek%*%%%k%u%gaw%%v%%%cu%%*yi%l%%%%%i%%w%fy%va%%%%%*%h%%*y%%%%%%a%n%%o%"
        "a%v%mj*%*%*f%*no%%nq**oywg%n%*u%ni%fxoa%f*pp*qfd%fygd%*%pzv%skhj%%qh%%%%%%"
        "z*%%%bdj%l%ahyct%%%qll%uh*%ltb%zh*j%tw%%%*%*%*oa%%%absg%qs**puurp%pebx%*nh"
        "muj%c%tw%ca%*%%k%wu%%zv%k%%x%%%%up%qovx*%yb%**uv%%xr%ohp%%s%e%%tt%izp%%i%%"
        "%sz%ay%rln*wukn*o%kzq%k%%iqj%%jv%ku*i%%%*iya%%%fx*e%%%j*%gd%uc%%rq%%c%%ga%"
        "h*%o*rm%y%s%*%%j%kt%v%%%%%%%*eafh%nu*%%kwh%n%gq*k*%tl%%%%%lr%%bs%*%%%t*%%*"
        "%m%bl*%%%o*%%*a%%%d%%%t%g%%lxai%%lzl%xz%%%%aeg%eklfch%fk*b%b%%%%*cdz*ii%%%"
        "gu%%h%%%%efm%pwz%nnb%zq%%u*%%%%gg%%ff%r%ygwbz%s%t%%a%uu%az%i%tlwwoswbby*we"
        "a%%*m%%*ayya*u%uiq%*%v%ded%v*bz*%%%olv*%iul%%%c%d%%%b%*n%d%%%w%ib%ezxstyj*"
        "%%p%%c%%*q**%x*%%nxms*r*z%t**%%%tn%%xi%%*v%%oxs*%l%%xm%%s%%p*%%hhbfaod%fye"
        "%%e%h%*i*u%k%g%muijgqb%*v*%e%ech%**%%**%%**s%*s%%%%%%ok%%c*%p%*vpv%m%*%%%%"
        "a%*d%t%*%%%h%%s%%sjg%%wfk%k%f%is%o%%%p*%%%xb*nl%*k%y%*pnmbv%%flixxtwirff%w"
        "t%jy%%fb%%h%zqs*tn%ne*%p*h%%d*k%lvq%py*f%z%c%%%hk%%a%%jfrxi%y%%*%%ee%%b%b%"
        "%%d%z%*%mr%%*%b%*%*%wk%%fx%oygl%ior%%odx%%ffo**s%lrm%o%*%t%h%%fmjlk*vek*%y"
        "pu%y%%%wvl%%u%spnlv%*q%%*s**%i%v%%%r%n*%bm%or%%%%k%%w%mnakz%*gt%fou%x*qzm%"
        "*hi*%%q%%%**%k*%jzwt%q*%%e*jmstgnz%%*i%%*%p%qcpa%**%*p%%fs*y*yb%mb%%sh%%u%"
        "%m%%fw*%*vi%*%%%n*y*sx*%thab*jfiz%hqklv*q*ptruo%l%wvoulw*%hv%mpue%d**cnq%p"
        "%f%%%e%%*up%%xld%wfds%*x%%%q%rr%%%w*%vmu%x%pi%r%h%%%itp%*%%%%%%b*kh%%i%%%%"
        "%dwrkf%%%%%w", 264856462843842, 'y' },
};

int main() {
	Solution sol;
	int case_num = 1;
	for (auto& [input, k, expected] : test_cases) {
		auto result = sol.processStr(input, k);
		cout << "Case " << case_num << ": "
			 << (result == expected ? "PASS" : "FAIL")
			 << endl;
	}
	return 0;
}