.PHONY: lint test

default: lint test

lint:
	find . -name "*.js" -maxdepth 0 | grep -v "benchmark/\|node_modules/\|scripts/" | xargs node_modules/jshint/bin/jshint

test:
	node_modules/mocha/bin/mocha --reporter spec --ui tdd
