{
  'targets': [
    {
      'target_name': 'addon',
      'sources': [ 'src/addon.cc', 'src/hashset.cc' ],
      'cflags': [ '-stdlib=libc++', '-std=c++11' ],
      'ldflags': [ '-stdlib=libc++', '-std=c++11' ],
      'xcode_settings': {
        'OTHER_CPLUSPLUSFLAGS': [ '-mmacosx-version-min=10.7', '-stdlib=libc++', '-std=c++11' ],
        'OTHER_LDFLAGS': [ '-std=c++11' ],
      },
    }
  ]
}
