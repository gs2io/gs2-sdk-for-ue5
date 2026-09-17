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
#include "Datastore/Model/Cache/DataObject.h"
#include "Datastore/Model/Cache/DataObjectHistory.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Datastore::Domain::Model
{

    FDataObjectDomain::FDataObjectDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Datastore::Domain::FGs2DatastoreDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<FString> DataObjectName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Datastore::FGs2DatastoreRestClient>(Gs2->RestSession)),
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
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        DataObjectName(From.DataObjectName),
        ParentKey(From.ParentKey)
    {

    }

    FDataObjectDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FDataObjectDomain>& Self,
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
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithDataObjectName(Self->DataObjectName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->UpdateDataObjectByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();

            if (ResultModel.IsValid() && ResultModel->GetItem() != nullptr)
            {

        if (!ResultModel.IsValid() || !((ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>())).IsSet())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("userId"), TEXT("userId is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }
        Gs2::Datastore::Model::Cache::FDataObjectCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            (ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>()),
            Request->GetDataObjectName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
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
        const TSharedPtr<FDataObjectDomain>& Self,
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
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithDataObjectName(Self->DataObjectName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->PrepareReUploadByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();

            if (ResultModel.IsValid() && ResultModel->GetItem() != nullptr)
            {

        if (!ResultModel.IsValid() || !((ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>())).IsSet())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("userId"), TEXT("userId is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }
        Gs2::Datastore::Model::Cache::FDataObjectCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            (ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>()),
            Request->GetDataObjectName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        auto Domain = Self;
        if (ResultModel != nullptr)
        {
            if (ResultModel->GetUploadUrl().IsSet())
            {
                Domain->UploadUrl = *ResultModel->GetUploadUrl();
            }
        }

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FDataObjectDomain::FPrepareReUploadTask>> FDataObjectDomain::PrepareReUpload(
        Request::FPrepareReUploadByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FPrepareReUploadTask>>(this->AsShared(), Request);
    }

    FDataObjectDomain::FDoneUploadTask::FDoneUploadTask(
        const TSharedPtr<FDataObjectDomain>& Self,
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
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithDataObjectName(Self->DataObjectName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->DoneUploadByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();

            if (ResultModel.IsValid() && ResultModel->GetItem() != nullptr)
            {

        if (!ResultModel.IsValid() || !((ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>())).IsSet())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("userId"), TEXT("userId is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }
        Gs2::Datastore::Model::Cache::FDataObjectCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            (ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>()),
            Request->GetDataObjectName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
        Self->Gs2->Cache->ClearListCache(
            Gs2::Datastore::Model::FDataObjectHistory::TypeName,
            Gs2::Datastore::Model::Cache::FDataObjectHistoryCache::CreateCacheParentKey(
                Request->GetNamespaceName(),
                Request->GetUserId(),
                Request->GetDataObjectName(),
                TOptional<int32>()
            )
        );
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
        const TSharedPtr<FDataObjectDomain>& Self,
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
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithDataObjectName(Self->DataObjectName);
        const auto Future = Self->Client->DeleteDataObjectByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            const auto Error = Future->GetTask().Error();
            if (Error.IsValid() && Error->IsChildOf(Gs2::Core::Model::FNotFoundError::Class))
            {
                *Result = Self;
                return nullptr;
            }
            return Error;
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();

            if (ResultModel.IsValid() && ResultModel->GetItem() != nullptr)
            {

        if (!ResultModel.IsValid() || !((ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>())).IsSet())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("userId"), TEXT("userId is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }
        Gs2::Datastore::Model::Cache::FDataObjectCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            (ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>()),
            Request->GetDataObjectName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
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

    FDataObjectDomain::FPrepareDownloadByUserIdAndDataObjectNameTask::FPrepareDownloadByUserIdAndDataObjectNameTask(
        const TSharedPtr<FDataObjectDomain>& Self,
        const Request::FPrepareDownloadByUserIdAndDataObjectNameRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FDataObjectDomain::FPrepareDownloadByUserIdAndDataObjectNameTask::FPrepareDownloadByUserIdAndDataObjectNameTask(
        const FPrepareDownloadByUserIdAndDataObjectNameTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDataObjectDomain::FPrepareDownloadByUserIdAndDataObjectNameTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Datastore::Domain::Model::FDataObjectDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
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
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();

            if (ResultModel.IsValid() && ResultModel->GetItem() != nullptr)
            {

        if (!ResultModel.IsValid() || !((ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>())).IsSet())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("userId"), TEXT("userId is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }
        Gs2::Datastore::Model::Cache::FDataObjectCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            (ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>()),
            Request->GetDataObjectName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        auto Domain = Self;
        if (ResultModel != nullptr)
        {
            if (ResultModel->GetFileUrl().IsSet())
            {
                Domain->FileUrl = *ResultModel->GetFileUrl();
            }
            if (ResultModel->GetContentLength().IsSet())
            {
                Domain->ContentLength = *ResultModel->GetContentLength();
            }
        }

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FDataObjectDomain::FPrepareDownloadByUserIdAndDataObjectNameTask>> FDataObjectDomain::PrepareDownloadByUserIdAndDataObjectName(
        Request::FPrepareDownloadByUserIdAndDataObjectNameRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FPrepareDownloadByUserIdAndDataObjectNameTask>>(this->AsShared(), Request);
    }

    FDataObjectDomain::FPrepareDownloadByUserIdAndDataObjectNameAndGenerationTask::FPrepareDownloadByUserIdAndDataObjectNameAndGenerationTask(
        const TSharedPtr<FDataObjectDomain>& Self,
        const Request::FPrepareDownloadByUserIdAndDataObjectNameAndGenerationRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FDataObjectDomain::FPrepareDownloadByUserIdAndDataObjectNameAndGenerationTask::FPrepareDownloadByUserIdAndDataObjectNameAndGenerationTask(
        const FPrepareDownloadByUserIdAndDataObjectNameAndGenerationTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDataObjectDomain::FPrepareDownloadByUserIdAndDataObjectNameAndGenerationTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Datastore::Domain::Model::FDataObjectDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
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
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();

            if (ResultModel.IsValid() && ResultModel->GetItem() != nullptr)
            {

        if (!ResultModel.IsValid() || !((ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>())).IsSet())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("userId"), TEXT("userId is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }
        Gs2::Datastore::Model::Cache::FDataObjectCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            (ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>()),
            Request->GetDataObjectName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        auto Domain = Self;
        if (ResultModel != nullptr)
        {
            if (ResultModel->GetFileUrl().IsSet())
            {
                Domain->FileUrl = *ResultModel->GetFileUrl();
            }
            if (ResultModel->GetContentLength().IsSet())
            {
                Domain->ContentLength = *ResultModel->GetContentLength();
            }
        }

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FDataObjectDomain::FPrepareDownloadByUserIdAndDataObjectNameAndGenerationTask>> FDataObjectDomain::PrepareDownloadByUserIdAndDataObjectNameAndGeneration(
        Request::FPrepareDownloadByUserIdAndDataObjectNameAndGenerationRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FPrepareDownloadByUserIdAndDataObjectNameAndGenerationTask>>(this->AsShared(), Request);
    }

    Gs2::Datastore::Domain::Iterator::FDescribeDataObjectHistoriesByUserIdIteratorPtr FDataObjectDomain::DataObjectHistories(
        const TOptional<FString> TimeOffsetToken
    ) const
    {
        return MakeShared<Gs2::Datastore::Domain::Iterator::FDescribeDataObjectHistoriesByUserIdIterator>(
            Gs2,
            Client,
            NamespaceName,
            UserId,
            DataObjectName,
            TimeOffsetToken
        );
    }

    Gs2::Core::Domain::CallbackID FDataObjectDomain::SubscribeDataObjectHistories(
    TFunction<void()> Callback

    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Datastore::Model::FDataObjectHistory::TypeName,
            Gs2::Datastore::Model::Cache::FDataObjectHistoryCache::CreateCacheParentKey(
                NamespaceName,
                UserId,
                DataObjectName,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FDataObjectDomain::UnsubscribeDataObjectHistories(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Datastore::Model::FDataObjectHistory::TypeName,
            Gs2::Datastore::Model::Cache::FDataObjectHistoryCache::CreateCacheParentKey(
                NamespaceName,
                UserId,
                DataObjectName,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FDataObjectDomain::FCollectDataObjectHistoriesTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Datastore::Model::FDataObjectHistoryPtr>>, public TSharedFromThis<FCollectDataObjectHistoriesTask>
    {
        const TSharedPtr<FDataObjectDomain> Self;
        const TFunction<void(TArray<Gs2::Datastore::Model::FDataObjectHistoryPtr>)> OnCollected;
    const TOptional<FString> QueryTimeOffsetToken;
    public:
        explicit FCollectDataObjectHistoriesTask(const TSharedPtr<FDataObjectDomain>& Self, TFunction<void(TArray<Gs2::Datastore::Model::FDataObjectHistoryPtr>)> OnCollected,const TOptional<FString> TimeOffsetToken) : Self(Self), OnCollected(OnCollected), QueryTimeOffsetToken(TimeOffsetToken) {}
        FCollectDataObjectHistoriesTask(const FCollectDataObjectHistoriesTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Datastore::Model::FDataObjectHistoryPtr>>> Result) override
        {
            TArray<Gs2::Datastore::Model::FDataObjectHistoryPtr> Items;
            auto Iterator = Self->DataObjectHistories(QueryTimeOffsetToken)->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Datastore::Model::FDataObjectHistoryPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FDataObjectDomain::SubscribeDataObjectHistories(
        TFunction<void(TArray<Gs2::Datastore::Model::FDataObjectHistoryPtr>)> Callback,const TOptional<FString> TimeOffsetToken
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Datastore::Domain::FGs2DatastoreDomain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryUserId = UserId;
        const auto QueryDataObjectName = DataObjectName;
        const auto QueryTimeOffsetToken = TimeOffsetToken;
        const auto Parent = Gs2::Datastore::Model::Cache::FDataObjectHistoryCache::CreateCacheParentKey(
        NamespaceName,
        UserId,
        DataObjectName,
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Datastore::Model::FDataObjectHistory::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Datastore::Model::FDataObjectHistoryPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Datastore::Model::FDataObjectHistory>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryUserId, QueryDataObjectName, QueryTimeOffsetToken]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FDataObjectDomain>(Owner, WeakService.Pin(), QueryNamespaceName, QueryUserId, QueryDataObjectName);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectDataObjectHistoriesTask>>(Domain, Callback, QueryTimeOffsetToken);
                Task->StartBackgroundTask();
            }
        );
    }

    void FDataObjectDomain::InvalidateDataObjectHistories(const TOptional<FString> TimeOffsetToken)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Datastore::Model::FDataObjectHistory::TypeName,
            Gs2::Datastore::Model::Cache::FDataObjectHistoryCache::CreateCacheParentKey(
        NamespaceName,
        UserId,
        DataObjectName,
        TOptional<int32>()
    )
        );
    }

    FDataObjectDomain::FSubscribeDataObjectHistoriesWithInitialCallTask::FSubscribeDataObjectHistoriesWithInitialCallTask(const TSharedPtr<FDataObjectDomain>& Self, TFunction<void(TArray<Gs2::Datastore::Model::FDataObjectHistoryPtr>)> Callback,const TOptional<FString> TimeOffsetToken) : Self(Self), Callback(Callback), QueryTimeOffsetToken(TimeOffsetToken) {}
    FDataObjectDomain::FSubscribeDataObjectHistoriesWithInitialCallTask::FSubscribeDataObjectHistoriesWithInitialCallTask(const FSubscribeDataObjectHistoriesWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
    Gs2::Core::Model::FGs2ErrorPtr FDataObjectDomain::FSubscribeDataObjectHistoriesWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectDataObjectHistoriesTask>>(Self, TFunction<void(TArray<Gs2::Datastore::Model::FDataObjectHistoryPtr>)>(), QueryTimeOffsetToken);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeDataObjectHistories(Callback, QueryTimeOffsetToken);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FDataObjectDomain::FSubscribeDataObjectHistoriesWithInitialCallTask>> FDataObjectDomain::SubscribeDataObjectHistoriesWithInitialCall(TFunction<void(TArray<Gs2::Datastore::Model::FDataObjectHistoryPtr>)> Callback,const TOptional<FString> TimeOffsetToken)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeDataObjectHistoriesWithInitialCallTask>>(this->AsShared(), Callback, TimeOffsetToken);
    }

    TSharedPtr<Gs2::Datastore::Domain::Model::FDataObjectHistoryDomain> FDataObjectDomain::DataObjectHistory(
        const FString Generation
    )
    {
        return MakeShared<Gs2::Datastore::Domain::Model::FDataObjectHistoryDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId,
            DataObjectName,
            Generation == TEXT("") ? TOptional<FString>() : TOptional<FString>(Generation)
        );
    }

    FString FDataObjectDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> DataObjectName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (DataObjectName.IsSet() ? *DataObjectName : "null") + ":" +
            ChildType;
    }

    FString FDataObjectDomain::CreateCacheKey(
        TOptional<FString> DataObjectName
    )
    {
        return FString("") +
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
        const auto CacheParentKey = Gs2::Datastore::Model::Cache::FDataObjectCache::CreateCacheParentKey(

            Self->NamespaceName,
            Self->UserId,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::Datastore::Model::Cache::FDataObjectCache::CreateCacheKey(

            Self->DataObjectName
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Datastore::Model::FDataObject::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Datastore::Model::FDataObjectPtr Value;
                const auto CacheHit = Gs2::Datastore::Model::Cache::FDataObjectCache::TryGet(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->UserId,
                    Self->DataObjectName,
                    TOptional<int32>(),
                    &Value
                );
                if (CacheHit)
                {
                    *Result = Value;
                    return nullptr;
                }
                *Result = Value;
                return nullptr;
            }
        );
    }

    TSharedPtr<FAsyncTask<FDataObjectDomain::FModelTask>> FDataObjectDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FDataObjectDomain::FModelTask>>(this->AsShared());
    }

    void FDataObjectDomain::Invalidate()
    {
        Gs2::Datastore::Model::Cache::FDataObjectCache::Delete(
            Gs2->Cache,

            NamespaceName,
            UserId,
            DataObjectName,
            TOptional<int32>()
        );
    }

    FDataObjectDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FDataObjectDomain>& Self,
        TFunction<void(Gs2::Datastore::Model::FDataObjectPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FDataObjectDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDataObjectDomain::FSubscribeWithInitialCallTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result
    )
    {
        const auto Task = Self->Model();
        Task->StartSynchronousTask();
        Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Item = Task->GetTask().Result();
        const auto CallbackId = Self->Subscribe(Callback);
        Callback(Item);
        *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FDataObjectDomain::FSubscribeWithInitialCallTask>> FDataObjectDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Datastore::Model::FDataObjectPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FDataObjectDomain::Subscribe(
        TFunction<void(Gs2::Datastore::Model::FDataObjectPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Datastore::Model::Cache::FDataObjectCache::CreateCacheParentKey(

            NamespaceName,
            UserId,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Datastore::Model::Cache::FDataObjectCache::CreateCacheKey(

            DataObjectName
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Datastore::Domain::FGs2DatastoreDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryUserId = UserId;
        const TOptional<FString> QueryDataObjectName = DataObjectName;
        return Gs2->Cache->Subscribe(
            Gs2::Datastore::Model::FDataObject::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Datastore::Model::FDataObject>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryUserId, QueryDataObjectName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FDataObjectDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    QueryUserId,
                    QueryDataObjectName
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FDataObjectDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Datastore::Model::Cache::FDataObjectCache::CreateCacheParentKey(

            NamespaceName,
            UserId,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Datastore::Model::Cache::FDataObjectCache::CreateCacheKey(

            DataObjectName
        );
        Gs2->Cache->Unsubscribe(
            Gs2::Datastore::Model::FDataObject::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            CallbackID
        );
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif
