/**
 * Copyright (c) 2026 Huawei Technologies Co., Ltd.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * 自包含 Jest 配置（通过 --config jest/jest.config.js 使用，
 * 不读取根目录 jest.config.js / jest.setup.ts / package.json 中的 jest 字段）。
 * 转译方案：@babel/preset-typescript 剥离 TS 类型（isTSX 支持 .tsx），
 * @babel/plugin-transform-react-jsx 编译 JSX（classic runtime），
 * @babel/plugin-transform-modules-commonjs 转为 CommonJS。
 */

const path = require('path');

module.exports = {
  // 用绝对路径归一化，避免 Windows 下 rootDir 含 '..' 造成覆盖率数据路径不匹配
  rootDir: path.join(__dirname, '..'),
  testEnvironment: 'node',
  transform: {
    '^.+\\.(js|jsx|ts|tsx)$': [
      'babel-jest',
      {
        presets: [
          ['@babel/preset-typescript', { isTSX: true, allExtensions: true }],
        ],
        plugins: [
          '@babel/plugin-transform-react-jsx',
          '@babel/plugin-transform-modules-commonjs',
          '@babel/plugin-proposal-class-properties',
        ],
      },
    ],
  },
  moduleFileExtensions: ['ts', 'tsx', 'js', 'jsx', 'json', 'node'],
  testMatch: [
    '<rootDir>/jest/__tests__/**/*-test.ts',
    '<rootDir>/jest/__tests__/**/*-test.tsx',
  ],
  setupFiles: ['<rootDir>/jest/jest.setup.js'],
  globals: {
    __DEV__: true,
  },
  transformIgnorePatterns: [
    'node_modules/(?!react-native|@react-native|react)',
  ],
  collectCoverageFrom: [
    'src/**/*.{ts,tsx}',
    '!src/**/__tests__/**',
    // codegen 声明文件：类型剥离后仅剩 import + export default codegen(...) 调用，
    // 其可执行语句全部由 modules-commonjs 插件生成，会被 babel-jest 的
    // auxiliaryCommentBefore('istanbul ignore next') 自动排除，行覆盖永远为 0%。
    // 行为已由 *-test 断言覆盖（注册名/导出/可渲染），按 codegen spec 惯例排除出指标。
    '!src/**/*NativeComponent.ts',
  ],
  coverageThreshold: {
    global: { branches: 60 },
  },
};
