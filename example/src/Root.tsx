import React, { useState } from 'react';
import { StyleSheet, SafeAreaView, Text, TouchableOpacity, View } from 'react-native';
import { NavigationContainer } from '@react-navigation/native';

import App from './examples/App';

export default function Root() {
  const [page, setPage] = useState<'entry' | 'tester'>('entry');
  const [showUnavailableHint, setShowUnavailableHint] = useState(false);

  if (page === 'entry') {
    return (
      <NavigationContainer>
        <SafeAreaView style={styles.container}>
          <View style={styles.section}>
            <Text style={styles.title}>NestedScroll Tester</Text>
            <TouchableOpacity
              style={styles.button}
              onPress={() => {
                setShowUnavailableHint(false);
                setPage('tester');
              }}>
              <Text style={styles.buttonText}>rnt</Text>
            </TouchableOpacity>
            <TouchableOpacity
              style={[styles.button, styles.buttonDisabled]}
              onPress={() => setShowUnavailableHint(true)}>
              <Text style={styles.buttonTextDisabled}>原库demo</Text>
            </TouchableOpacity>
            {showUnavailableHint && (
              <Text style={styles.hint}>原库demo 暂未接入，无法跳转</Text>
            )}
          </View>
        </SafeAreaView>
      </NavigationContainer>
    );
  }

  return (
    <NavigationContainer>
      <SafeAreaView style={styles.container}>
        <View style={styles.backBar}>
          <TouchableOpacity
            style={styles.backTouch}
            onPress={() => setPage('entry')}>
            <Text style={styles.backText}>&lt; 返回</Text>
          </TouchableOpacity>
        </View>
        <App />
      </SafeAreaView>
    </NavigationContainer>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    backgroundColor: '#F5FCFF',
  },
  section: {
    flex: 1,
    alignItems: 'center',
    paddingTop: 120,
    padding: 24,
  },
  title: {
    fontSize: 22,
    fontWeight: 'bold',
    color: '#333',
    marginBottom: 48,
  },
  button: {
    width: 220,
    paddingVertical: 14,
    borderRadius: 8,
    backgroundColor: '#007AFF',
    alignItems: 'center',
    marginBottom: 16,
  },
  buttonText: {
    fontSize: 16,
    color: '#fff',
    fontWeight: 'bold',
  },
  buttonDisabled: {
    backgroundColor: '#c7c7cc',
  },
  buttonTextDisabled: {
    fontSize: 16,
    color: '#f2f2f7',
    fontWeight: 'bold',
  },
  hint: {
    fontSize: 12,
    color: '#999',
    marginTop: 8,
  },
  backBar: {
    backgroundColor: '#f8f8f8',
    borderBottomWidth: 1,
    borderBottomColor: '#e0e0e0',
  },
  backTouch: {
    padding: 10,
    alignSelf: 'flex-start',
  },
  backText: {
    fontSize: 15,
    color: '#007AFF',
  },
});
