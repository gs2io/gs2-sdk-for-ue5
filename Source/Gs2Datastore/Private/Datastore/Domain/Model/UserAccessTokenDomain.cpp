/*
 * Copyright 2016 Game Server Services, Inc. or its affiliates. All Rights
 * Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4458) // Declaration hides class member
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow" // declaration shadows a field of
#endif

#include "Datastore/Domain/Model/UserAccessToken.h"
#include "Datastore/Domain/Model/User.h"
#include "Datastore/Domain/Model/Namespace.h"
#include "Datastore/Domain/Model/DataObject.h"
#include "Datastore/Domain/Model/DataObjectAccessToken.h"
#include "Datastore/Domain/Model/DataObjectHistory.h"
#include "Datastore/Domain/Model/DataObjectHistoryAccessToken.h"
#include "Datastore/Domain/Model/User.h"
#include "Datastore/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::Datastore::Domain::Model
{

    FUserAccessTokenDomain::FUserAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Datastore::Domain::FGs2DatastoreDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Datastore::FGs2DatastoreRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        ParentKey(Gs2::Datastore::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "User"
        ))
    {
    }

    FUserAccessTokenDomain::FUserAccessTokenDomain(
        const FUserAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        ParentKey(From.ParentKey)
    {

    }

    FUserAccessTokenDomain::FPrepareUploadTask::FPrepareUploadTask(
        const TSharedPtr<FUserAccessTokenDomain>& Self,
        const Request::FPrepareUploadRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserAccessTokenDomain::FPrepareUploadTask::FPrepareUploadTask(
        const FPrepareUploadTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserAccessTokenDomain::FPrepareUploadTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Datastore::Domain::Model::FDataObjectAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken());
        auto Domain = MakeShared<Gs2::Datastore::Domain::Model::FDataObjectAccessTokenDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            Self->AccessToken,
            ResultModel->GetItem()->GetName()
        );
        if (ResultModel != nullptr)
        {
            Domain->UploadUrl = *ResultModel->GetUploadUrl();
        }

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserAccessTokenDomain::FPrepareUploadTask>> FUserAccessTokenDomain::PrepareUpload(
        Request::FPrepareUploadRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FPrepareUploadTask>>(this->AsShared(), Request);
    }

    FUserAccessTokenDomain::FPrepareDownloadTask::FPrepareDownloadTask(
        const TSharedPtr<FUserAccessTokenDomain>& Self,
        const Request::FPrepareDownloadRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserAccessTokenDomain::FPrepareDownloadTask::FPrepareDownloadTask(
        const FPrepareDownloadTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserAccessTokenDomain::FPrepareDownloadTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Datastore::Domain::Model::FDataObjectAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken());
        auto Domain = MakeShared<Gs2::Datastore::Domain::Model::FDataObjectAccessTokenDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            Self->AccessToken,
            ResultModel->GetItem()->GetName()
        );
        if (ResultModel != nullptr)
        {
            Domain->FileUrl = *ResultModel->GetFileUrl();
            Domain->ContentLength = *ResultModel->GetContentLength();
        }

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserAccessTokenDomain::FPrepareDownloadTask>> FUserAccessTokenDomain::PrepareDownload(
        Request::FPrepareDownloadRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FPrepareDownloadTask>>(this->AsShared(), Request);
    }

    FUserAccessTokenDomain::FPrepareDownloadByGenerationTask::FPrepareDownloadByGenerationTask(
        const TSharedPtr<FUserAccessTokenDomain>& Self,
        const Request::FPrepareDownloadByGenerationRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserAccessTokenDomain::FPrepareDownloadByGenerationTask::FPrepareDownloadByGenerationTask(
        const FPrepareDownloadByGenerationTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserAccessTokenDomain::FPrepareDownloadByGenerationTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Datastore::Domain::Model::FDataObjectAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken());
        auto Domain = MakeShared<Gs2::Datastore::Domain::Model::FDataObjectAccessTokenDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            Self->AccessToken,
            ResultModel->GetItem()->GetName()
        );
        if (ResultModel != nullptr)
        {
            Domain->FileUrl = *ResultModel->GetFileUrl();
            Domain->ContentLength = *ResultModel->GetContentLength();
        }

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserAccessTokenDomain::FPrepareDownloadByGenerationTask>> FUserAccessTokenDomain::PrepareDownloadByGeneration(
        Request::FPrepareDownloadByGenerationRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FPrepareDownloadByGenerationTask>>(this->AsShared(), Request);
    }

    Gs2::Datastore::Domain::Iterator::FDescribeDataObjectsIteratorPtr FUserAccessTokenDomain::DataObjects(
        const TOptional<FString> Status
    ) const
    {
        return MakeShared<Gs2::Datastore::Domain::Iterator::FDescribeDataObjectsIterator>(
            Gs2,
            Client,
            NamespaceName,
            AccessToken,
            Status
        );
    }

    Gs2::Core::Domain::CallbackID FUserAccessTokenDomain::SubscribeDataObjects(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Datastore::Model::FDataObject::TypeName,
            Gs2::Datastore::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId(),
                "DataObject"
            ),
            Callback
        );
    }

    void FUserAccessTokenDomain::UnsubscribeDataObjects(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Datastore::Model::FDataObject::TypeName,
            Gs2::Datastore::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId(),
                "DataObject"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Datastore::Domain::Model::FDataObjectAccessTokenDomain> FUserAccessTokenDomain::DataObject(
        const FString DataObjectName
    )
    {
        return MakeShared<Gs2::Datastore::Domain::Model::FDataObjectAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken,
            DataObjectName == TEXT("") ? TOptional<FString>() : TOptional<FString>(DataObjectName)
        );
    }

    FString FUserAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            ChildType;
    }

    FString FUserAccessTokenDomain::CreateCacheKey(
        TOptional<FString> UserId
    )
    {
        return FString("") +
            (UserId.IsSet() ? *UserId : "null");
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

