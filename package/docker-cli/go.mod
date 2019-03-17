module github.com/docker/cli

// v18.09.2
replace github.com/docker/docker => github.com/docker/engine v0.0.0-20190206233949-eb137ff1765f

// In-tree pflag fixup
replace github.com/spf13/pflag => ./thirdparty/pflag

// Derived from vendor.conf with go mod init
require (
	cloud.google.com/go v0.37.0 // indirect
	github.com/Azure/go-ansiterm v0.0.0-20170929234023-d6e3b3328b78 // indirect
	github.com/Jeffail/gabs v1.2.0 // indirect
	github.com/Microsoft/go-winio v0.4.10 // indirect
	github.com/Microsoft/hcsshim v0.0.0-20180822151309-44c060121b68 // indirect
	github.com/Nvveen/Gotty v0.0.0-20120604004816-cd527374f1e5
	github.com/Shopify/logrus-bugsnag v0.0.0-20171204204709-577dee27f20d // indirect
	github.com/agl/ed25519 v0.0.0-20170116200512-5312a6153412 // indirect
	github.com/asaskevich/govalidator v0.0.0-20180720115003-f9ffefc3facf // indirect
	github.com/bitly/go-hostpool v0.0.0-20171023180738-a3a6125de932 // indirect
	github.com/bitly/go-simplejson v0.5.0 // indirect
	github.com/bmizerany/assert v0.0.0-20160611221934-b7ed37b82869 // indirect
	github.com/boltdb/bolt v1.3.1 // indirect
	github.com/bugsnag/bugsnag-go v1.4.0 // indirect
	github.com/bugsnag/panicwrap v1.2.0 // indirect
	github.com/cenkalti/backoff v2.1.1+incompatible // indirect
	github.com/cloudflare/cfssl v0.0.0-20181213083726-b94e044bb51e // indirect
	github.com/containerd/cgroups v0.0.0-20190226200435-dbea6f2bd416 // indirect
	github.com/containerd/console v0.0.0-20180822173158-c12b1e7919c1
	github.com/containerd/containerd v0.0.0-20180912143703-bb0f83ab6eec
	github.com/containerd/continuity v0.0.0-20180216233310-d8fb8589b0e8 // indirect
	github.com/containerd/fifo v0.0.0-20180307165137-3d5202aec260 // indirect
	github.com/containerd/typeurl v0.0.0-20170912152501-f6943554a7e7 // indirect
	github.com/coreos/go-systemd v0.0.0-20190212144455-93d5ec2c7f76 // indirect
	github.com/cpuguy83/go-md2man v1.0.8
	github.com/denisenkom/go-mssqldb v0.0.0-20190315220205-a8ed825ac853 // indirect
	github.com/dgrijalva/jwt-go v2.6.0+incompatible // indirect
	github.com/docker/distribution v0.0.0-20180327202408-83389a148052
	github.com/docker/docker v0.0.0-00010101000000-000000000000
	github.com/docker/docker-credential-helpers v0.6.1
	github.com/docker/go v0.0.0-20160303222718-d30aec9fd63c // indirect
	github.com/docker/go-connections v0.4.0
	github.com/docker/go-events v0.0.0-20170721190031-9461782956ad // indirect
	github.com/docker/go-metrics v0.0.0-20170502235133-d466d4f6fd96 // indirect
	github.com/docker/go-units v0.3.3
	github.com/docker/libtrust v0.0.0-20150526203908-9cbd2a1374f4 // indirect
	github.com/docker/licensing v0.0.0-20181018214158-1c117a1720cb
	github.com/docker/swarmkit v0.0.0-20180820032850-cfa742c8abe6
	github.com/erikstmartin/go-testdb v0.0.0-20160219214506-8d10e4a1bae5 // indirect
	github.com/flynn-archive/go-shlex v0.0.0-20150515145356-3f9db97f8568
	github.com/go-sql-driver/mysql v1.4.1 // indirect
	github.com/godbus/dbus v4.1.0+incompatible // indirect
	github.com/gofrs/uuid v3.2.0+incompatible // indirect
	github.com/gogo/googleapis v0.0.0-20180501115203-b23578765ee5 // indirect
	github.com/gogo/protobuf v1.1.1
	github.com/golang/glog v0.0.0-20160126235308-23def4e6c14b
	github.com/golang/groupcache v0.0.0-20190129154638-5b532d6fd5ef // indirect
	github.com/google/certificate-transparency-go v1.0.21 // indirect
	github.com/google/go-cmp v0.2.0
	github.com/google/gofuzz v0.0.0-20170612174753-24818f796faf // indirect
	github.com/google/shlex v0.0.0-20150127133951-6f45313302b9 // indirect
	github.com/googleapis/gnostic v0.2.0 // indirect
	github.com/gorilla/context v1.1.1 // indirect
	github.com/gorilla/mux v1.6.2 // indirect
	github.com/grpc-ecosystem/go-grpc-prometheus v1.2.0 // indirect
	github.com/grpc-ecosystem/grpc-opentracing v0.0.0-20180507213350-8e809c8a8645 // indirect
	github.com/hailocab/go-hostpool v0.0.0-20160125115350-e80d13ce29ed // indirect
	github.com/hashicorp/go-version v0.0.0-20180322230233-23480c066577
	github.com/hashicorp/golang-lru v0.0.0-20180201235237-0fb14efe8c47 // indirect
	github.com/imdario/mergo v0.3.6
	github.com/inconshreveable/mousetrap v1.0.0 // indirect
	github.com/jinzhu/gorm v1.9.2 // indirect
	github.com/jinzhu/inflection v0.0.0-20180308033659-04140366298a // indirect
	github.com/jinzhu/now v1.0.0 // indirect
	github.com/json-iterator/go v0.0.0-20180701071628-ab8a2e0c74be // indirect
	github.com/kardianos/osext v0.0.0-20190222173326-2bc1f35cddc0 // indirect
	github.com/lib/pq v1.0.0 // indirect
	github.com/mattn/go-shellwords v1.0.3
	github.com/mattn/go-sqlite3 v1.10.0 // indirect
	github.com/miekg/pkcs11 v0.0.0-20180425180052-287d9350987c // indirect
	github.com/mitchellh/mapstructure v1.1.2
	github.com/moby/buildkit v0.0.0-20181005022200-520201006c9d
	github.com/modern-go/concurrent v0.0.0-20180306012644-bacd9c7ef1dd // indirect
	github.com/modern-go/reflect2 v0.0.0-20180701023420-4b7aa43c6742 // indirect
	github.com/morikuni/aec v0.0.0-20170113033406-39771216ff4c
	github.com/onsi/ginkgo v1.8.0 // indirect
	github.com/onsi/gomega v1.5.0 // indirect
	github.com/opencontainers/go-digest v1.0.0-rc1
	github.com/opencontainers/image-spec v1.0.1
	github.com/opencontainers/runc v0.0.0-20180815054256-20aff4f0488c // indirect
	github.com/opencontainers/runtime-spec v1.0.1
	github.com/opentracing/opentracing-go v0.0.0-20171003133519-1361b9cd60be // indirect
	github.com/peterbourgon/diskv v2.0.1+incompatible // indirect
	github.com/pkg/errors v0.0.0-20161002052512-839d9e913e06
	github.com/satori/go.uuid v0.0.0-20151028231719-d41af8bb6a77 // indirect
	github.com/sirupsen/logrus v1.0.6
	github.com/spf13/cobra v0.0.3
	github.com/spf13/pflag v1.0.4-0.20181223182923-24fa6976df40
	github.com/spf13/viper v1.3.2 // indirect
	github.com/stretchr/testify v1.3.0 // indirect
	github.com/syndtr/gocapability v0.0.0-20150716010906-2c00daeb6c3b // indirect
	github.com/theupdateframework/notary v0.6.1
	github.com/tonistiigi/fsutil v0.0.0-20181002165410-f567071bed24
	github.com/tonistiigi/units v0.0.0-20180711220420-6950e57a87ea // indirect
	github.com/xeipuuv/gojsonpointer v0.0.0-20180127040702-4e3ac2762d5f // indirect
	github.com/xeipuuv/gojsonreference v0.0.0-20180127040603-bd5ef7bd5415 // indirect
	github.com/xeipuuv/gojsonschema v0.0.0-20160323030313-93e72a773fad
	github.com/xlab/handysort v0.0.0-20150421192137-fb3537ed64a1 // indirect
	golang.org/x/crypto v0.0.0-20181203042331-505ab145d0a9
	golang.org/x/sync v0.0.0-20190227155943-e225da77a7e6
	golang.org/x/sys v0.0.0-20181205085412-a5c9d58dba9a
	golang.org/x/text v0.3.1-0.20180807135948-17ff2d5776d2
	golang.org/x/time v0.0.0-20181108054448-85acf8d2951c
	gopkg.in/airbrake/gobrake.v2 v2.0.9 // indirect
	gopkg.in/dancannon/gorethink.v3 v3.0.5 // indirect
	gopkg.in/fatih/pool.v2 v2.0.0 // indirect
	gopkg.in/gemnasium/logrus-airbrake-hook.v2 v2.1.2 // indirect
	gopkg.in/gorethink/gorethink.v3 v3.0.5 // indirect
	gopkg.in/yaml.v2 v2.2.2
	gotest.tools v2.1.0+incompatible
	k8s.io/api v0.0.0-20180712090710-2d6f90ab1293
	k8s.io/apimachinery v0.0.0-20180621070125-103fd098999d
	k8s.io/client-go v0.0.0-20180806134042-1f13a808da65
	k8s.io/kube-openapi v0.0.0-20180719232738-d8ea2fe547a4 // indirect
	k8s.io/kubernetes v1.11.2
	vbom.ml/util v0.0.0-20170409195630-256737ac55c4
)
