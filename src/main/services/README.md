# Services

Create here projects that export internal interface of services.
Implementation of internal interface does not have security checks like
identifying user role, checking login session to run specific operation.
Its more about to get requested data and store it by request.

For example, you can have two applications: admin application and client application (usual scenario).
Both applications make calls to same services. Admin can browse all user profiles.
Client can view and edit only its own profile. But behind it, both - admin and client applications
make calls to same "Profile" service to get and store data.

Don't put application specific logic here.