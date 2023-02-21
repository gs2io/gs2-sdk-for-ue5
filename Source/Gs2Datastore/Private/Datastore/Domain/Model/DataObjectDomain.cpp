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

    FDataObjectDomain::FDataObjectDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<FString> DataObjectName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Datastore::FGs2DatastoreRestClient>(Session)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        DataObjectName(DataObjectName),
        ParentKey(Gs2::Datastore::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId,
            "DataObject"
        ))
    {
    }

    FDataObjectDomain::FDataObjectDomain(
        const FDataObjectDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FDataObjectDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FDataObjectDomain> Self,
        const Request::FUpdateDataObjectByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FDataObjectDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDataObjectDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Datastore::Domain::Model::FDataObjectDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithDataObjectName(Self->DataObjectName);
        const auto Future = Self->Client->UpdateDataObjectByUserId(
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
                Self->Cache->Put<Gs2::Datastore::Model::FDataObject>(
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

    TSharedPtr<FAsyncTask<FDataObjectDomain::FUpdateTask>> FDataObjectDomain::Update(
        Request::FUpdateDataObjectByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FDataObjectDomain::FPrepareReUploadTask::FPrepareReUploadTask(
        const TSharedPtr<FDataObjectDomain> Self,
        const Request::FPrepareReUploadByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FDataObjectDomain::FPrepareReUploadTask::FPrepareReUploadTask(
        const FPrepareReUploadTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDataObjectDomain::FPrepareReUploadTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Datastore::Domain::Model::FDataObjectDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithDataObjectName(Self->DataObjectName);
        const auto Future = Self->Client->PrepareReUploadByUserId(
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
                Self->Cache->Put<Gs2::Datastore::Model::FDataObject>(
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

    TSharedPtr<FAsyncTask<FDataObjectDomain::FPrepareReUploadTask>> FDataObjectDomain::PrepareReUpload(
        Request::FPrepareReUploadByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FPrepareReUploadTask>>(this->AsShared(), Request);
    }

    FDataObjectDomain::FDoneUploadTask::FDoneUploadTask(
        const TSharedPtr<FDataObjectDomain> Self,
        const Request::FDoneUploadByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FDataObjectDomain::FDoneUploadTask::FDoneUploadTask(
        const FDoneUploadTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDataObjectDomain::FDoneUploadTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Datastore::Domain::Model::FDataObjectDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithDataObjectName(Self->DataObjectName);
        const auto Future = Self->Client->DoneUploadByUserId(
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
                Self->Cache->Put<Gs2::Datastore::Model::FDataObject>(
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
                Self->Cache->ClearListCache<Gs2::Datastore::Model::FDataObjectHistory>(
                    Gs2::Datastore::Domain::Model::FDataObjectDomain::CreateCacheParentKey(
                        Self->NamespaceName,
                        Self->UserId,
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

    TSharedPtr<FAsyncTask<FDataObjectDomain::FDoneUploadTask>> FDataObjectDomain::DoneUpload(
        Request::FDoneUploadByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDoneUploadTask>>(this->AsShared(), Request);
    }

    FDataObjectDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FDataObjectDomain> Self,
        const Request::FDeleteDataObjectByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FDataObjectDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDataObjectDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Datastore::Domain::Model::FDataObjectDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithDataObjectName(Self->DataObjectName);
        const auto Future = Self->Client->DeleteDataObjectByUserId(
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
                Self->Cache->Put<Gs2::Datastore::Model::FDataObject>(
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

    TSharedPtr<FAsyncTask<FDataObjectDomain::FDeleteTask>> FDataObjectDomain::Delete(
        Request::FDeleteDataObjectByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FDataObjectDomain::FPrepareDownloadByUserIdAndNameTask::FPrepareDownloadByUserIdAndNameTask(
        const TSharedPtr<FDataObjectDomain> Self,
        const Request::FPrepareDownloadByUserIdAndDataObjectNameRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FDataObjectDomain::FPrepareDownloadByUserIdAndNameTask::FPrepareDownloadByUserIdAndNameTask(
        const FPrepareDownloadByUserIdAndNameTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDataObjectDomain::FPrepareDownloadByUserIdAndNameTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Datastore::Domain::Model::FDataObjectDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithDataObjectName(Self->DataObjectName);
        const auto Future = Self->Client->PrepareDownloadByUserIdAndDataObjectName(
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
                Self->Cache->Put<Gs2::Datastore::Model::FDataObject>(
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

    TSharedPtr<FAsyncTask<FDataObjectDomain::FPrepareDownloadByUserIdAndNameTask>> FDataObjectDomain::PrepareDownloadByUserIdAndName(
        Request::FPrepareDownloadByUserIdAndDataObjectNameRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FPrepareDownloadByUserIdAndNameTask>>(this->AsShared(), Request);
    }

    FDataObjectDomain::FPrepareDownloadByUserIdAndNameAndGenerationTask::FPrepareDownloadByUserIdAndNameAndGenerationTask(
        const TSharedPtr<FDataObjectDomain> Self,
        const Request::FPrepareDownloadByUserIdAndDataObjectNameAndGenerationRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FDataObjectDomain::FPrepareDownloadByUserIdAndNameAndGenerationTask::FPrepareDownloadByUserIdAndNameAndGenerationTask(
        const FPrepareDownloadByUserIdAndNameAndGenerationTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDataObjectDomain::FPrepareDownloadByUserIdAndNameAndGenerationTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Datastore::Domain::Model::FDataObjectDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithDataObjectName(Self->DataObjectName);
        const auto Future = Self->Client->PrepareDownloadByUserIdAndDataObjectNameAndGeneration(
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
                Self->Cache->Put<Gs2::Datastore::Model::FDataObject>(
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

    TSharedPtr<FAsyncTask<FDataObjectDomain::FPrepareDownloadByUserIdAndNameAndGenerationTask>> FDataObjectDomain::PrepareDownloadByUserIdAndNameAndGeneration(
        Request::FPrepareDownloadByUserIdAndDataObjectNameAndGenerationRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FPrepareDownloadByUserIdAndNameAndGenerationTask>>(this->AsShared(), Request);
    }

    Gs2::Datastore::Domain::Iterator::FDescribeDataObjectHistoriesByUserIdIteratorPtr FDataObjectDomain::DataObjectHistories(
    ) const
    {
        return MakeShared<Gs2::Datastore::Domain::Iterator::FDescribeDataObjectHistoriesByUserIdIterator>(
            Cache,
            Client,
            NamespaceName,
            UserId,
            DataObjectName
        );
    }

    TSharedPtr<Gs2::Datastore::Domain::Model::FDataObjectHistoryDomain> FDataObjectDomain::DataObjectHistory(
        const FString Generation
    ) const
    {
        return MakeShared<Gs2::Datastore::Domain::Model::FDataObjectHistoryDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName,
            UserId,
            DataObjectName,
            Generation
        );
    }

    FString FDataObjectDomain::CreateCacheParentKey(
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

    FString FDataObjectDomain::CreateCacheKey(
        TOptional<FString> DataObjectName
    )
    {
        return FString() +
            (DataObjectName.IsSet() ? *DataObjectName : "null");
    }

    FDataObjectDomain::FModelTask::FModelTask(
        const TSharedPtr<FDataObjectDomain> Self
    ): Self(Self)
    {

    }

    FDataObjectDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FDataObjectDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Datastore::Model::FDataObject>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        auto Value = Self->Cache->Get<Gs2::Datastore::Model::FDataObject>(
            Self->ParentKey,
            Gs2::Datastore::Domain::Model::FDataObjectDomain::CreateCacheKey(
                Self->DataObjectName
            )
        );
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FDataObjectDomain::FModelTask>> FDataObjectDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FDataObjectDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

