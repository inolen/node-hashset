{
  'targets': [
    {
      'target_name': 'addon',
      'sources': [ 'src/addon.cc' ],
      'cflags': [ '-std=c++11' ],
      'ldflags': [ '-std=c++11' ],
      'conditions': [
        ['OS=="mac"',
          {
            'cflags': [ '-stdlib=libc++' ],
            'xcode_settings': {
              'OTHER_CPLUSPLUSFLAGS': [ '-mmacosx-version-min=10.7', '-stdlib=libc++', '-std=c++11' ],
              'OTHER_LDFLAGS': [ '-std=c++11' ],
            }
          }
        ],
      ]
    }
  ]
}
