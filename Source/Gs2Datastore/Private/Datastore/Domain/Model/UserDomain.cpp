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

#include "Datastore/Domain/Model/User.h"
#include "Datastore/Domain/Model/Namespace.h"
#include "Datastore/Domain/Model/DataObject.h"
#include "Datastore/Domain/Model/DataObjectAccessToken.h"
#include "Datastore/Domain/Model/DataObjectHistory.h"
#include "Datastore/Domain/Model/DataObjectHistoryAccessToken.h"
#include "Datastore/Domain/Model/User.h"
#include "Datastore/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Datastore::Domain::Model
{

    FUserDomain::FUserDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Datastore::FGs2DatastoreRestClient>(Session)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        ParentKey(Gs2::Datastore::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "User"
        ))
    {
    }

    FUserDomain::FUserDomain(
        const FUserDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FUserDomain::FPrepareUploadTask::FPrepareUploadTask(
        const TSharedPtr<FUserDomain> Self,
        const Request::FPrepareUploadByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserDomain::FPrepareUploadTask::FPrepareUploadTask(
        const FPrepareUploadTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FPrepareUploadTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Datastore::Domain::Model::FDataObjectDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->PrepareUploadByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Datastore::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "DataObject"
                );
                const auto Key = Gs2::Datastore::Domain::Model::FDataObjectDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Datastore::Model::FDataObject::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::Datastore::Domain::Model::FDataObjectDomain>(
            Self->Cache,
            Self->JobQueueDomain,
            Self->StampSheetConfiguration,
            Self->Session,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetUserId(),
            ResultModel->GetItem()->GetName()
        );
        Domain->UploadUrl = *ResultModel->GetUploadUrl();

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserDomain::FPrepareUploadTask>> FUserDomain::PrepareUpload(
        Request::FPrepareUploadByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FPrepareUploadTask>>(this->AsShared(), Request);
    }

    FUserDomain::FPrepareDownloadTask::FPrepareDownloadTask(
        const TSharedPtr<FUserDomain> Self,
        const Request::FPrepareDownloadByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserDomain::FPrepareDownloadTask::FPrepareDownloadTask(
        const FPrepareDownloadTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FPrepareDownloadTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Datastore::Domain::Model::FDataObjectDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->PrepareDownloadByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Datastore::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "DataObject"
                );
                const auto Key = Gs2::Datastore::Domain::Model::FDataObjectDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Datastore::Model::FDataObject::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::Datastore::Domain::Model::FDataObjectDomain>(
            Self->Cache,
            Self->JobQueueDomain,
            Self->StampSheetConfiguration,
            Self->Session,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetUserId(),
            ResultModel->GetItem()->GetName()
        );
        Domain->FileUrl = *ResultModel->GetFileUrl();
        Domain->ContentLength = *ResultModel->GetContentLength();

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserDomain::FPrepareDownloadTask>> FUserDomain::PrepareDownload(
        Request::FPrepareDownloadByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FPrepareDownloadTask>>(this->AsShared(), Request);
    }

    FUserDomain::FPrepareDownloadByGenerationTask::FPrepareDownloadByGenerationTask(
        const TSharedPtr<FUserDomain> Self,
        const Request::FPrepareDownloadByGenerationAndUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserDomain::FPrepareDownloadByGenerationTask::FPrepareDownloadByGenerationTask(
        const FPrepareDownloadByGenerationTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FPrepareDownloadByGenerationTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Datastore::Domain::Model::FDataObjectDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->PrepareDownloadByGenerationAndUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Datastore::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "DataObject"
                );
                const auto Key = Gs2::Datastore::Domain::Model::FDataObjectDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Datastore::Model::FDataObject::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::Datastore::Domain::Model::FDataObjectDomain>(
            Self->Cache,
            Self->JobQueueDomain,
            Self->StampSheetConfiguration,
            Self->Session,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetUserId(),
            ResultModel->GetItem()->GetName()
        );
        Domain->FileUrl = *ResultModel->GetFileUrl();
        Domain->ContentLength = *ResultModel->GetContentLength();

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserDomain::FPrepareDownloadByGenerationTask>> FUserDomain::PrepareDownloadByGeneration(
        Request::FPrepareDownloadByGenerationAndUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FPrepareDownloadByGenerationTask>>(this->AsShared(), Request);
    }

    Gs2::Datastore::Domain::Iterator::FDescribeDataObjectsByUserIdIteratorPtr FUserDomain::DataObjects(
        const TOptional<FString> Status
    ) const
    {
        return MakeShared<Gs2::Datastore::Domain::Iterator::FDescribeDataObjectsByUserIdIterator>(
            Cache,
            Client,
            NamespaceName,
            UserId,
            Status
        );
    }

    TSharedPtr<Gs2::Datastore::Domain::Model::FDataObjectDomain> FUserDomain::DataObject(
        const FString DataObjectName
    ) const
    {
        return MakeShared<Gs2::Datastore::Domain::Model::FDataObjectDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName,
            UserId,
            DataObjectName
        );
    }

    FString FUserDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        FString ChildType
    )
    {
        return FString() +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            ChildType;
    }

    FString FUserDomain::CreateCacheKey(
        TOptional<FString> UserId
    )
    {
        return FString() +
            (UserId.IsSet() ? *UserId : "null");
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

