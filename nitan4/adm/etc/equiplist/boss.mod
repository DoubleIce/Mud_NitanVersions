// 套装组合列表文件表
// boss.xml
// BOSS专用套装
// 序号从7000到7999

// restore_variable 可处理转换 string "([\"ads\":20,])" 为 mapping 格式

#eqlist
// 套装的部件
<A3000>
<type>armor/armor</type>
<name>$CYNGRN$龙鳞甲$NOR$</name>
<id>dragon armor</id>
<value>10000</value>
<mod>M3000</mod>
<enchase>
apply_prop/armor:60
apply_prop/str:2
apply_prop/con:2
apply_prop/force:2
</enchase>
</A3000>

<A3001>
<type>armor/surcoat</type>
<name>$CYNGRN$龙神披风$NOR$</name>
<id>dragon surcoat</id>
<value>10000</value>
<mod>M3000</mod>
<enchase>
apply_prop/armor:10
apply_prop/str:2
apply_prop/dex:1
apply_prop/dodge:1
</enchase>
</A3001>

<A3002>
<type>armor/waist</type>
<name>$CYNGRN$龙之束带$NOR$</name>
<id>dragon waist</id>
<value>10000</value>
<mod>M3000</mod>
<enchase>
apply_prop/armor:30
apply_prop/str:2
apply_prop/int:2
</enchase>
</A3002>

<A3003>
<type>armor/head</type>
<name>$CYNGRN$恶龙之触$NOR$</name>
<id>dragon head</id>
<value>10000</value>
<mod>M3000</mod>
<enchase>
apply_prop/armor:36
apply_prop/str:2
apply_prop/con:2
</enchase>
</A3003>

<A3004>
<type>armor/boots</type>
<name>$CYNGRN$龙骨胫甲$NOR$</name>
<id>dragon boots</id>
<value>10000</value>
<mod>M3000</mod>
<enchase>
apply_prop/armor:20
apply_prop/dex:2
apply_prop/str:2
</enchase>
</A3004>


#modlist
// 对应的套装
<M3000>
<name>$CYNGRN$龙之神力$NOR$</name>
<file>
A3000
A3001
A3002
A3003
A3004
</file>
<stats>
avoid_locked:20
add_locked:20
add_busy:10
reduce_busy:20
avoid_busy:20
add_xuruo:10
avoid_xuruo:20
add_damage:20
reduce_damage:20
</stats>
</M3000>

#listend

// 套装效果  注重攻击、伤害加强
<M3001>
<name>$HBBLU$破坏神之灭(神)</name>
<file>
A3010
A3011
A3012
A3013
A3014
A3015
</file>
<stats>
attack:700
damage:9000
ap_power:90
da_power:90
add_locked:90
add_damage:90
add_busy:9
</stats>
</M3001>


//六个配件
<A3010>
<type>armor/armor</type>
<name>$HBBLU$破坏神战甲</name>
<id>pohuai armor</id>
<long>（神品）此装备只是瞧上一眼，已经让人杀意腾腾、血脉喷张、战意无穷。</long>
<value>30000000</value>
<mod>M3001</mod>
<enchase>
apply_prop/attack:150
apply_prop/ap_power:25
apply_prop/da_power:25
</enchase>
</A3010>

<A3011>
<type>armor/surcoat</type>
<name>$HBBLU$破坏神披风</name>
<id>pohuai surcoat</id>
<long>（神品）此装备只是瞧上一眼，已经让人杀意腾腾、血脉喷张、战意无穷。</long>
<value>30000000</value>
<mod>M3001</mod>
<enchase>
apply_prop/attack:150
apply_prop/damage:800
apply_prop/ap_power:25
</enchase>
</A3011>

<A3012>
<type>armor/waist</type>
<name>$HBBLU$破坏神腰带</name>
<id>pohuai waist</id>
<long>（神品）此装备只是瞧上一眼，已经让人杀意腾腾、血脉喷张、战意无穷。</long>
<value>30000000</value>
<mod>M3001</mod>
<enchase>
apply_prop/damage:700
apply_prop/da_power:25
apply_prop/add_busy:3
</enchase>
</A3012>

<A3013>
<type>armor/head</type>
<name>$HBBLU$破坏神头盔</name>
<id>pohuai head</id>
<long>（神品）此装备只是瞧上一眼，已经让人杀意腾腾、血脉喷张、战意无穷。</long>
<value>30000000</value>
<mod>M3001</mod>
<enchase>
apply_prop/attack:150
apply_prop/da_power:25
apply_prop/add_busy:2
</enchase>
</A3013>

<A3014>
<type>armor/boots</type>
<name>$HBBLU$破坏神战靴</name>
<id>pohuai boots</id>
<long>（神品）此装备只是瞧上一眼，已经让人杀意腾腾、血脉喷张、战意无穷。</long>
<value>30000000</value>
<mod>M3001</mod>
<enchase>
apply_prop/attack:150
apply_prop/damage:500
apply_prop/ap_power:25
</enchase>
</A3014>

<A3015>
<type>armor/wrists</type>
<name>$HBBLU$破坏神护腕</name>
<id>pohuai wrists</id>
<long>（神品）此装备只是瞧上一眼，已经让人杀意腾腾、血脉喷张、战意无穷。</long>
<value>30000000</value>
<mod>M3001</mod>
<enchase>
apply_prop/ap_power:25
apply_prop/attack:150
apply_prop/damage:500
</enchase>
</A3015>
