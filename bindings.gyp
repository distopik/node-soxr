{
  'targets': [
    {
      'target_name': 'bindings',
      'sources': [
        'src/bindings.cc',
      ],
      "include_dirs" : [
        '<!(node -e "require(\'nan\')")'
      ],
      'dependencies': [
      ],
      'conditions':[
        ['OS=="win"', {
        'defines':[
          'NOMINMAX'
        ]
        }]
      ]
    }
  ]
}
