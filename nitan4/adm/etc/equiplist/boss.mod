// ��װ����б��ļ���
// boss.xml
// BOSSר����װ
// ��Ŵ�7000��7999

// restore_variable �ɴ���ת�� string "([\"ads\":20,])" Ϊ mapping ��ʽ

#eqlist
// ��װ�Ĳ���
<A3000>
<type>armor/armor</type>
<name>$CYNGRN$���ۼ�$NOR$</name>
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
<name>$CYNGRN$��������$NOR$</name>
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
<name>$CYNGRN$��֮����$NOR$</name>
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
<name>$CYNGRN$����֮��$NOR$</name>
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
<name>$CYNGRN$�����ּ�$NOR$</name>
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
// ��Ӧ����װ
<M3000>
<name>$CYNGRN$��֮����$NOR$</name>
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

// ��װЧ��  ע�ع������˺���ǿ
<M3001>
<name>$HBBLU$�ƻ���֮��(��)</name>
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


//�������
<A3010>
<type>armor/armor</type>
<name>$HBBLU$�ƻ���ս��</name>
<id>pohuai armor</id>
<long>����Ʒ����װ��ֻ������һ�ۣ��Ѿ�����ɱ�����ڡ�Ѫ�����š�ս�����</long>
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
<name>$HBBLU$�ƻ�������</name>
<id>pohuai surcoat</id>
<long>����Ʒ����װ��ֻ������һ�ۣ��Ѿ�����ɱ�����ڡ�Ѫ�����š�ս�����</long>
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
<name>$HBBLU$�ƻ�������</name>
<id>pohuai waist</id>
<long>����Ʒ����װ��ֻ������һ�ۣ��Ѿ�����ɱ�����ڡ�Ѫ�����š�ս�����</long>
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
<name>$HBBLU$�ƻ���ͷ��</name>
<id>pohuai head</id>
<long>����Ʒ����װ��ֻ������һ�ۣ��Ѿ�����ɱ�����ڡ�Ѫ�����š�ս�����</long>
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
<name>$HBBLU$�ƻ���սѥ</name>
<id>pohuai boots</id>
<long>����Ʒ����װ��ֻ������һ�ۣ��Ѿ�����ɱ�����ڡ�Ѫ�����š�ս�����</long>
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
<name>$HBBLU$�ƻ�����</name>
<id>pohuai wrists</id>
<long>����Ʒ����װ��ֻ������һ�ۣ��Ѿ�����ɱ�����ڡ�Ѫ�����š�ս�����</long>
<value>30000000</value>
<mod>M3001</mod>
<enchase>
apply_prop/ap_power:25
apply_prop/attack:150
apply_prop/damage:500
</enchase>
</A3015>
