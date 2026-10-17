import React, {useState} from 'react';
import {
  ScrollView,
  StyleSheet,
  Text,
  TouchableOpacity,
  View,
} from 'react-native';
import {
  NestedScrollView,
  NestedScrollViewHeader,
} from '@react-native-ohos/react-native-nested-scroll';

const MODES = ['auto', 'none', 'box-only', 'box-none'] as const;
type PointerEventsMode = (typeof MODES)[number];

function ModeSelector({
  label,
  value,
  onChange,
}: {
  label: string;
  value: PointerEventsMode;
  onChange: (mode: PointerEventsMode) => void;
}) {
  return (
    <View style={styles.selectorRow}>
      <Text style={styles.selectorLabel}>{label}</Text>
      <View style={styles.selector}>
        {MODES.map(mode => (
          <TouchableOpacity
            key={mode}
            style={[styles.modeBtn, value === mode && styles.modeBtnActive]}
            onPress={() => onChange(mode)}>
            <Text
              style={value === mode ? styles.modeTextActive : styles.modeText}>
              {mode}
            </Text>
          </TouchableOpacity>
        ))}
      </View>
    </View>
  );
}

function NestedScrollPointerEvents() {
  const [scrollMode, setScrollMode] = useState<PointerEventsMode>('auto');
  const [headerMode, setHeaderMode] = useState<PointerEventsMode>('auto');
  const [lastEvent, setLastEvent] = useState('(尚未触发)');

  const mark = (message: string) => setLastEvent(message);

  return (
    <View style={styles.container}>
      <View style={styles.panel}>
        <ModeSelector
          label="NestedScrollView:"
          value={scrollMode}
          onChange={mode => {
            setScrollMode(mode);
            mark(`NestedScrollView pointerEvents: ${mode}`);
          }}
        />
        <ModeSelector
          label="Header:"
          value={headerMode}
          onChange={mode => {
            setHeaderMode(mode);
            mark(`Header pointerEvents: ${mode}`);
          }}
        />
        <Text style={styles.log}>最近事件: {lastEvent}</Text>
      </View>

      <View style={styles.stage}>
        <View style={styles.behind} pointerEvents="box-none">
          {new Array(40).fill(0).map((_, idx) => (
            <TouchableOpacity
              key={idx}
              style={styles.behindBtn}
              onPress={() => mark(`背景按钮 ${idx + 1}`)}>
              <Text style={styles.behindText}>背景 {idx + 1}</Text>
            </TouchableOpacity>
          ))}
        </View>

        <NestedScrollView
          style={styles.coordinator}
          bounces={false}
          pointerEvents={scrollMode}>
          <NestedScrollViewHeader
            stickyHeight={44}
            pointerEvents={headerMode}
            onTouchStart={() => mark('Header onTouchStart 触发')}>
            <TouchableOpacity
              style={styles.headerCell}
              onPress={() => mark('Header 按钮（折叠区）')}>
              <Text style={styles.headerText}>Header 按钮（折叠区）</Text>
            </TouchableOpacity>
            <View style={styles.stickyBar}>
              <Text style={styles.headerText}>sticky 区域</Text>
              <TouchableOpacity
                style={styles.stickyBtn}
                onPress={() => mark('Header 按钮（sticky 区）')}>
                <Text style={styles.stickyBtnText}>点我</Text>
              </TouchableOpacity>
            </View>
          </NestedScrollViewHeader>

          <View style={styles.content}>
            {new Array(3).fill(0).map((_, idx) => (
              <TouchableOpacity
                key={idx}
                style={[
                  styles.contentCell,
                  {backgroundColor: idx % 2 ? 'pink' : 'beige'},
                ]}
                onPress={() => mark(`内容按钮 ${idx + 1}`)}>
                <Text style={styles.contentText}>内容按钮 {idx + 1}</Text>
              </TouchableOpacity>
            ))}

            <View style={styles.innerWrap}>
              <ScrollView style={styles.innerScroll}>
                {new Array(15).fill(0).map((_, idx) => (
                  <TouchableOpacity
                    key={idx}
                    style={styles.innerCell}
                    onPress={() => mark(`内层按钮 ${idx + 1}`)}>
                    <Text style={styles.contentText}>内层按钮 {idx + 1}</Text>
                  </TouchableOpacity>
                ))}
              </ScrollView>
            </View>
          </View>
        </NestedScrollView>
      </View>
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: '#fff',
  },
  panel: {
    paddingHorizontal: 10,
    paddingVertical: 8,
    borderBottomWidth: StyleSheet.hairlineWidth,
    borderBottomColor: '#999',
  },
  selectorRow: {
    flexDirection: 'row',
    alignItems: 'center',
    marginVertical: 4,
  },
  selectorLabel: {
    width: 130,
    fontSize: 13,
    color: '#333',
  },
  selector: {
    flex: 1,
    flexDirection: 'row',
  },
  modeBtn: {
    flex: 1,
    paddingVertical: 6,
    borderWidth: 1,
    borderColor: '#2089dc',
    borderRadius: 4,
    marginHorizontal: 2,
    alignItems: 'center',
  },
  modeBtnActive: {
    backgroundColor: '#2089dc',
  },
  modeText: {
    fontSize: 12,
    color: '#2089dc',
  },
  modeTextActive: {
    fontSize: 12,
    color: '#fff',
  },
  log: {
    fontSize: 13,
    color: 'firebrick',
    marginTop: 4,
  },
  hint: {
    fontSize: 11,
    color: '#666',
    marginTop: 4,
    lineHeight: 16,
  },
  stage: {
    flex: 1,
  },
  behind: {
    ...StyleSheet.absoluteFillObject,
    flexDirection: 'row',
    flexWrap: 'wrap',
    alignContent: 'flex-start',
    backgroundColor: '#ffe3e3',
  },
  behindBtn: {
    width: 80,
    height: 60,
    margin: 6,
    borderRadius: 6,
    backgroundColor: '#ff9d9d',
    alignItems: 'center',
    justifyContent: 'center',
  },
  behindText: {
    fontSize: 13,
    color: '#7a1414',
  },
  coordinator: {
    flex: 1,
    backgroundColor: 'rgba(255, 255, 255, 0.93)',
  },
  headerCell: {
    height: 120,
    width: '80%',
    alignSelf: 'flex-start',
    alignItems: 'center',
    justifyContent: 'center',
    backgroundColor: '#d0e8ff',
  },
  headerText: {
    fontSize: 14,
    color: '#0b4f8a',
  },
  stickyBar: {
    height: 44,
    flexDirection: 'row',
    alignItems: 'center',
    justifyContent: 'space-between',
    paddingHorizontal: 16,
    backgroundColor: '#a8d4ff',
  },
  stickyBtn: {
    paddingHorizontal: 14,
    paddingVertical: 6,
    borderRadius: 4,
    backgroundColor: '#2089dc',
  },
  stickyBtnText: {
    fontSize: 12,
    color: '#fff',
  },
  content: {
    height: '88%',
    paddingBottom: 12,
  },
  contentCell: {
    height: 48,
    alignItems: 'center',
    justifyContent: 'center',
  },
  contentText: {
    fontSize: 14,
    color: '#333',
  },
  innerWrap: {
    flex: 1,
    margin: 10,
    borderWidth: 1,
    borderColor: '#2089dc',
    borderRadius: 6,
    overflow: 'hidden',
  },
  innerTitle: {
    fontSize: 13,
    color: '#2089dc',
    padding: 6,
    textAlign: 'center',
  },
  innerScroll: {
    flex: 1,
  },
  innerCell: {
    height: 44,
    alignItems: 'center',
    justifyContent: 'center',
    backgroundColor: '#eef6ff',
  },
});

export default NestedScrollPointerEvents;
