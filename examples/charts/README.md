This Helm chart installs the CephCluster and has been tested with Rook 1.2.4 and Ceph ceph/ceph:v14.2.6
Helm v3 is used to install these charts

The prerequisite is to create the kubernetes namespace in which the Ceph cluster needs to be deployed
Following are the commands used to deploy cluster in kubernetes namespace rook-ceph-kp

kubectl create  ns rook-ceph-kp

Clone the repo and change directory into it

The name of the helm chart is rook-ceph-helm-kp
helm install rook-ceph-helm-kp --namespace rook-ceph-kp .

helm list --namespace rook-ceph-kp
NAME             	NAMESPACE   	REVISION	UPDATED                                	STATUS  	CHART                  	APP VERSION
rook-ceph-helm-kp	rook-ceph-kp	1       	2020-02-14 21:25:06.008579726 +0000 UTC	deployed	rook-ceph-cluster-0.0.1	

Check the cephcluster with the below command
kubectl get cephcluster -n rook-ceph-kp
NAME           DATADIRHOSTPATH    MONCOUNT   AGE   STATE     HEALTH
rook-ceph-kp   /var/lib/rook-kp   2          20m   Created   HEALTH_WARN

Following pods are create and their required ClusterRole, ClusterRoleBindings, Role and RoleBindings are also
created
kubectl get pods -n rook-ceph-kp
NAME                                                    READY   STATUS      RESTARTS   AGE
rook-ceph-crashcollector-lenlmsdev24-568bfd74f6-jqklv   1/1     Running     0          14m
rook-ceph-crashcollector-lenlmsdev30-6db6f57d87-6mc2r   1/1     Running     0          14m
rook-ceph-mgr-a-998986448-2xwx2                         1/1     Running     0          14m
rook-ceph-mon-a-75889d7b75-9f5qw                        1/1     Running     0          14m
rook-ceph-mon-b-7b759d856c-r6jwz                        1/1     Running     0          14m
rook-ceph-osd-0-586ccb9f85-wcjzh                        1/1     Running     0          12m
rook-ceph-osd-1-5d95bb4c94-zgk2v                        1/1     Running     0          12m
rook-ceph-osd-prepare-lenlmsdev24-gmvm2                 0/1     Completed   0          14m

The values.yaml file has values to deploy the cephcluster on an exiting Rook installation
which can be done using https://rook.io/docs/rook/master/helm-operator.html

