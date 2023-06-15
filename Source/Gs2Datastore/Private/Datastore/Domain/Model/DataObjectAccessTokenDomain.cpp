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

#include "Datastore/Domain/Model/DataObjectAccessToken.h"
#include "Datastore/Domain/Model/DataObject.h"
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

    FDataObjectAccessTokenDomain::FDataObjectAccessTokenDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr AccessToken,
        const TOptional<FString> DataObjectName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Datastore::FGs2DatastoreRestClient>(Session)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        DataObjectName(DataObjectName),
        ParentKey(Gs2::Datastore::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId(),
            "DataObject"
        ))
    {
    }

    FDataObjectAccessTokenDomain::FDataObjectAccessTokenDomain(
        const FDataObjectAccessTokenDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FDataObjectAccessTokenDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FDataObjectAccessTokenDomain> Self,
        const Request::FUpdateDataObjectRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FDataObjectAccessTokenDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDataObjectAccessTokenDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Datastore::Domain::Model::FDataObjectAccessTokenDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithDataObjectName(Self->DataObjectName);
        const auto Future = Self->Client->UpdateDataObject(
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
                    Self->UserId(),
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
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FDataObjectAccessTokenDomain::FUpdateTask>> FDataObjectAccessTokenDomain::Update(
        Request::FUpdateDataObjectRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FDataObjectAccessTokenDomain::FPrepareReUploadTask::FPrepareReUploadTask(
        const TSharedPtr<FDataObjectAccessTokenDomain> Self,
        const Request::FPrepareReUploadRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FDataObjectAccessTokenDomain::FPrepareReUploadTask::FPrepareReUploadTask(
        const FPrepareReUploadTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDataObjectAccessTokenDomain::FPrepareReUploadTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Datastore::Domain::Model::FDataObjectAccessTokenDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithDataObjectName(Self->DataObjectName);
        const auto Future = Self->Client->PrepareReUpload(
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
                    Self->UserId(),
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
        auto Domain = Self;
        Domain->UploadUrl = *ResultModel->GetUploadUrl();

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FDataObjectAccessTokenDomain::FPrepareReUploadTask>> FDataObjectAccessTokenDomain::PrepareReUpload(
        Request::FPrepareReUploadRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FPrepareReUploadTask>>(this->AsShared(), Request);
    }

    FDataObjectAccessTokenDomain::FDoneUploadTask::FDoneUploadTask(
        const TSharedPtr<FDataObjectAccessTokenDomain> Self,
        const Request::FDoneUploadRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FDataObjectAccessTokenDomain::FDoneUploadTask::FDoneUploadTask(
        const FDoneUploadTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDataObjectAccessTokenDomain::FDoneUploadTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Datastore::Domain::Model::FDataObjectAccessTokenDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithDataObjectName(Self->DataObjectName);
        const auto Future = Self->Client->DoneUpload(
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
                    Self->UserId(),
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
                Self->Cache->ClearListCache(
                    Gs2::Datastore::Model::FDataObjectHistory::TypeName,
                    Gs2::Datastore::Domain::Model::FDataObjectDomain::CreateCacheParentKey(
                        Self->NamespaceName,
                        Self->UserId(),
                        Self->DataObjectName,
                        "DataObjectHistory"
                    )
                );
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FDataObjectAccessTokenDomain::FDoneUploadTask>> FDataObjectAccessTokenDomain::DoneUpload(
        Request::FDoneUploadRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDoneUploadTask>>(this->AsShared(), Request);
    }

    FDataObjectAccessTokenDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FDataObjectAccessTokenDomain> Self,
        const Request::FDeleteDataObjectRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FDataObjectAccessTokenDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDataObjectAccessTokenDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Datastore::Domain::Model::FDataObjectAccessTokenDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithDataObjectName(Self->DataObjectName);
        const auto Future = Self->Client->DeleteDataObject(
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
                    Self->UserId(),
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
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FDataObjectAccessTokenDomain::FDeleteTask>> FDataObjectAccessTokenDomain::Delete(
        Request::FDeleteDataObjectRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FDataObjectAccessTokenDomain::FPrepareDownloadOwnDataTask::FPrepareDownloadOwnDataTask(
        const TSharedPtr<FDataObjectAccessTokenDomain> Self,
        const Request::FPrepareDownloadOwnDataRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FDataObjectAccessTokenDomain::FPrepareDownloadOwnDataTask::FPrepareDownloadOwnDataTask(
        const FPrepareDownloadOwnDataTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDataObjectAccessTokenDomain::FPrepareDownloadOwnDataTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Datastore::Domain::Model::FDataObjectAccessTokenDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithDataObjectName(Self->DataObjectName);
        const auto Future = Self->Client->PrepareDownloadOwnData(
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
                    Self->UserId(),
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
        auto Domain = Self;
        Domain->FileUrl = *ResultModel->GetFileUrl();
        Domain->ContentLength = *ResultModel->GetContentLength();

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FDataObjectAccessTokenDomain::FPrepareDownloadOwnDataTask>> FDataObjectAccessTokenDomain::PrepareDownloadOwnData(
        Request::FPrepareDownloadOwnDataRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FPrepareDownloadOwnDataTask>>(this->AsShared(), Request);
    }

    FDataObjectAccessTokenDomain::FPrepareDownloadOwnDataByGenerationTask::FPrepareDownloadOwnDataByGenerationTask(
        const TSharedPtr<FDataObjectAccessTokenDomain> Self,
        const Request::FPrepareDownloadOwnDataByGenerationRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FDataObjectAccessTokenDomain::FPrepareDownloadOwnDataByGenerationTask::FPrepareDownloadOwnDataByGenerationTask(
        const FPrepareDownloadOwnDataByGenerationTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDataObjectAccessTokenDomain::FPrepareDownloadOwnDataByGenerationTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Datastore::Domain::Model::FDataObjectAccessTokenDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithDataObjectName(Self->DataObjectName);
        const auto Future = Self->Client->PrepareDownloadOwnDataByGeneration(
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
                    Self->UserId(),
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
        auto Domain = Self;
        Domain->FileUrl = *ResultModel->GetFileUrl();
        Domain->ContentLength = *ResultModel->GetContentLength();

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FDataObjectAccessTokenDomain::FPrepareDownloadOwnDataByGenerationTask>> FDataObjectAccessTokenDomain::PrepareDownloadOwnDataByGeneration(
        Request::FPrepareDownloadOwnDataByGenerationRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FPrepareDownloadOwnDataByGenerationTask>>(this->AsShared(), Request);
    }

    Gs2::Datastore::Domain::Iterator::FDescribeDataObjectHistoriesIteratorPtr FDataObjectAccessTokenDomain::DataObjectHistories(
    ) const
    {
        return MakeShared<Gs2::Datastore::Domain::Iterator::FDescribeDataObjectHistoriesIterator>(
            Cache,
            Client,
            NamespaceName,
            AccessToken,
            DataObjectName
        );
    }

    TSharedPtr<Gs2::Datastore::Domain::Model::FDataObjectHistoryAccessTokenDomain> FDataObjectAccessTokenDomain::DataObjectHistory(
        const FString Generation
    ) const
    {
        return MakeShared<Gs2::Datastore::Domain::Model::FDataObjectHistoryAccessTokenDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName,
            AccessToken,
            DataObjectName,
            Generation
        );
    }

    FString FDataObjectAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> DataObjectName,
        FString ChildType
    )
    {
        return FString() +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (DataObjectName.IsSet() ? *DataObjectName : "null") + ":" +
            ChildType;
    }

    FString FDataObjectAccessTokenDomain::CreateCacheKey(
        TOptional<FString> DataObjectName
    )
    {
        return FString() +
            (DataObjectName.IsSet() ? *DataObjectName : "null");
    }

    FDataObjectAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FDataObjectAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FDataObjectAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FDataObjectAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Datastore::Model::FDataObject>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Datastore::Model::FDataObject> Value;
        auto bCacheHit = Self->Cache->TryGet<Gs2::Datastore::Model::FDataObject>(
            Self->ParentKey,
            Gs2::Datastore::Domain::Model::FDataObjectDomain::CreateCacheKey(
                Self->DataObjectName
            ),
            &Value
        );
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FDataObjectAccessTokenDomain::FModelTask>> FDataObjectAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FDataObjectAccessTokenDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

