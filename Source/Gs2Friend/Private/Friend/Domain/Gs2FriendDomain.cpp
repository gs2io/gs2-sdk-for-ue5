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
 *
 * deny overwrite
 */

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4458) // Declaration hides class member
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow" // declaration shadows a field of
#endif

// ReSharper disable CppUnusedIncludeDirective

#include "Friend/Domain/Gs2Friend.h"
#include "Friend/Domain/Model/Namespace.h"
#include "Friend/Domain/Model/User.h"
#include "Friend/Domain/Model/UserAccessToken.h"
#include "Friend/Domain/Model/Profile.h"
#include "Friend/Domain/Model/Follow.h"
#include "Friend/Domain/Model/Friend.h"
#include "Friend/Domain/Model/BlackList.h"
#include "Friend/Domain/Model/FollowUser.h"
#include "Friend/Domain/Model/FriendUser.h"
#include "Friend/Domain/Model/SendFriendRequest.h"
#include "Friend/Domain/Model/ReceiveFriendRequest.h"
#include "Friend/Domain/Model/PublicProfile.h"
#include "Friend/Model/Cache/Profile.h"

#include "Friend/Model/Cache/Namespace.h"
#include "Friend/Model/Cache/Profile.h"
#include "Friend/Model/Cache/SendFriendRequest.h"
#include "Friend/Model/Cache/FriendRequest.h"
#include "Friend/Model/Cache/PublicProfile.h"
#include "Friend/Model/Cache/BlackList.h"
#include "Friend/Model/Cache/FollowUser.h"
#include "Friend/Model/Cache/Follow.h"
#include "Friend/Model/Cache/FriendUser.h"
#include "Friend/Model/Cache/Friend.h"
#include "Friend/Model/Cache/ReceiveFriendRequest.h"

#include "Core/Domain/Gs2.h"

namespace Gs2::Friend::Domain
{

    FGs2FriendDomain::FGs2FriendDomain(
        const Core::Domain::FGs2Ptr& Gs2
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Client(MakeShared<Gs2::Friend::FGs2FriendRestClient>(Gs2->RestSession)),
        ParentKey("friend")
    {
    }

    FGs2FriendDomain::FGs2FriendDomain(
        const FGs2FriendDomain& From
    ):
        Gs2(From.Gs2),
        Client(From.Client),
        ParentKey(From.ParentKey)
    {

    }

    FGs2FriendDomain::FCreateNamespaceTask::FCreateNamespaceTask(
        const TSharedPtr<FGs2FriendDomain>& Self,
        const Request::FCreateNamespaceRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2FriendDomain::FCreateNamespaceTask::FCreateNamespaceTask(
        const FCreateNamespaceTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2FriendDomain::FCreateNamespaceTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Friend::Domain::Model::FNamespaceDomain>> Result
    )
    {
        const auto Future = Self->Client->CreateNamespace(
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


        Gs2::Friend::Model::Cache::FNamespaceCache::Put(
            Self->Gs2->Cache,

            ResultModel->GetItem()->GetName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        auto Domain = MakeShared<Gs2::Friend::Domain::Model::FNamespaceDomain>(
            Self->Gs2,
            Self,
            ResultModel->GetItem()->GetName()
        );
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGs2FriendDomain::FCreateNamespaceTask>> FGs2FriendDomain::CreateNamespace(
        Request::FCreateNamespaceRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateNamespaceTask>>(this->AsShared(), Request);
    }

    FGs2FriendDomain::FDumpUserDataTask::FDumpUserDataTask(
        const TSharedPtr<FGs2FriendDomain>& Self,
        const Request::FDumpUserDataByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2FriendDomain::FDumpUserDataTask::FDumpUserDataTask(
        const FDumpUserDataTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2FriendDomain::FDumpUserDataTask::Action(
        TSharedPtr<TSharedPtr<FGs2FriendDomain>> Result
    )
    {
        const auto Future = Self->Client->DumpUserDataByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();

        const auto Domain = Self;
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGs2FriendDomain::FDumpUserDataTask>> FGs2FriendDomain::DumpUserData(
        Request::FDumpUserDataByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDumpUserDataTask>>(this->AsShared(), Request);
    }

    FGs2FriendDomain::FCheckDumpUserDataTask::FCheckDumpUserDataTask(
        const TSharedPtr<FGs2FriendDomain>& Self,
        const Request::FCheckDumpUserDataByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2FriendDomain::FCheckDumpUserDataTask::FCheckDumpUserDataTask(
        const FCheckDumpUserDataTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2FriendDomain::FCheckDumpUserDataTask::Action(
        TSharedPtr<TSharedPtr<FGs2FriendDomain>> Result
    )
    {
        const auto Future = Self->Client->CheckDumpUserDataByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();

        const auto Domain = Self;
        if (ResultModel != nullptr)
        {
            if (ResultModel->GetUrl().IsSet())
            {
                Self->Url = Domain->Url = ResultModel->GetUrl();
            }
        }
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGs2FriendDomain::FCheckDumpUserDataTask>> FGs2FriendDomain::CheckDumpUserData(
        Request::FCheckDumpUserDataByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCheckDumpUserDataTask>>(this->AsShared(), Request);
    }

    FGs2FriendDomain::FCleanUserDataTask::FCleanUserDataTask(
        const TSharedPtr<FGs2FriendDomain>& Self,
        const Request::FCleanUserDataByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2FriendDomain::FCleanUserDataTask::FCleanUserDataTask(
        const FCleanUserDataTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2FriendDomain::FCleanUserDataTask::Action(
        TSharedPtr<TSharedPtr<FGs2FriendDomain>> Result
    )
    {
        const auto Future = Self->Client->CleanUserDataByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();

        const auto Domain = Self;
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGs2FriendDomain::FCleanUserDataTask>> FGs2FriendDomain::CleanUserData(
        Request::FCleanUserDataByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCleanUserDataTask>>(this->AsShared(), Request);
    }

    FGs2FriendDomain::FCheckCleanUserDataTask::FCheckCleanUserDataTask(
        const TSharedPtr<FGs2FriendDomain>& Self,
        const Request::FCheckCleanUserDataByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2FriendDomain::FCheckCleanUserDataTask::FCheckCleanUserDataTask(
        const FCheckCleanUserDataTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2FriendDomain::FCheckCleanUserDataTask::Action(
        TSharedPtr<TSharedPtr<FGs2FriendDomain>> Result
    )
    {
        const auto Future = Self->Client->CheckCleanUserDataByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();

        const auto Domain = Self;
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGs2FriendDomain::FCheckCleanUserDataTask>> FGs2FriendDomain::CheckCleanUserData(
        Request::FCheckCleanUserDataByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCheckCleanUserDataTask>>(this->AsShared(), Request);
    }

    FGs2FriendDomain::FPrepareImportUserDataTask::FPrepareImportUserDataTask(
        const TSharedPtr<FGs2FriendDomain>& Self,
        const Request::FPrepareImportUserDataByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2FriendDomain::FPrepareImportUserDataTask::FPrepareImportUserDataTask(
        const FPrepareImportUserDataTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2FriendDomain::FPrepareImportUserDataTask::Action(
        TSharedPtr<TSharedPtr<FGs2FriendDomain>> Result
    )
    {
        const auto Future = Self->Client->PrepareImportUserDataByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();

        const auto Domain = Self;
        if (ResultModel != nullptr)
        {
            if (ResultModel->GetUploadToken().IsSet())
            {
                Self->UploadToken = Domain->UploadToken = ResultModel->GetUploadToken();
            }
            if (ResultModel->GetUploadUrl().IsSet())
            {
                Self->UploadUrl = Domain->UploadUrl = ResultModel->GetUploadUrl();
            }
        }
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGs2FriendDomain::FPrepareImportUserDataTask>> FGs2FriendDomain::PrepareImportUserData(
        Request::FPrepareImportUserDataByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FPrepareImportUserDataTask>>(this->AsShared(), Request);
    }

    FGs2FriendDomain::FImportUserDataTask::FImportUserDataTask(
        const TSharedPtr<FGs2FriendDomain>& Self,
        const Request::FImportUserDataByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2FriendDomain::FImportUserDataTask::FImportUserDataTask(
        const FImportUserDataTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2FriendDomain::FImportUserDataTask::Action(
        TSharedPtr<TSharedPtr<FGs2FriendDomain>> Result
    )
    {
        const auto Future = Self->Client->ImportUserDataByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();

        const auto Domain = Self;
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGs2FriendDomain::FImportUserDataTask>> FGs2FriendDomain::ImportUserData(
        Request::FImportUserDataByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FImportUserDataTask>>(this->AsShared(), Request);
    }

    FGs2FriendDomain::FCheckImportUserDataTask::FCheckImportUserDataTask(
        const TSharedPtr<FGs2FriendDomain>& Self,
        const Request::FCheckImportUserDataByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2FriendDomain::FCheckImportUserDataTask::FCheckImportUserDataTask(
        const FCheckImportUserDataTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2FriendDomain::FCheckImportUserDataTask::Action(
        TSharedPtr<TSharedPtr<FGs2FriendDomain>> Result
    )
    {
        const auto Future = Self->Client->CheckImportUserDataByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();

        const auto Domain = Self;
        if (ResultModel != nullptr)
        {
            if (ResultModel->GetUrl().IsSet())
            {
                Self->Url = Domain->Url = ResultModel->GetUrl();
            }
        }
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGs2FriendDomain::FCheckImportUserDataTask>> FGs2FriendDomain::CheckImportUserData(
        Request::FCheckImportUserDataByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCheckImportUserDataTask>>(this->AsShared(), Request);
    }

    Gs2::Friend::Domain::Iterator::FDescribeNamespacesIteratorPtr FGs2FriendDomain::Namespaces(
        const TOptional<FString> NamePrefix
    ) const
    {
        return MakeShared<Gs2::Friend::Domain::Iterator::FDescribeNamespacesIterator>(
            Gs2,
            Client,
            NamePrefix
        );
    }

    Gs2::Core::Domain::CallbackID FGs2FriendDomain::SubscribeNamespaces(
    TFunction<void()> Callback

    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Friend::Model::FNamespace::TypeName,
            Gs2::Friend::Model::Cache::FNamespaceCache::CreateCacheParentKey(
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FGs2FriendDomain::UnsubscribeNamespaces(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Friend::Model::FNamespace::TypeName,
            Gs2::Friend::Model::Cache::FNamespaceCache::CreateCacheParentKey(
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FGs2FriendDomain::FCollectNamespacesTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Friend::Model::FNamespacePtr>>, public TSharedFromThis<FCollectNamespacesTask>
    {
        const TSharedPtr<FGs2FriendDomain> Self;
        const TFunction<void(TArray<Gs2::Friend::Model::FNamespacePtr>)> OnCollected;
    const TOptional<FString> QueryNamePrefix;
    public:
        explicit FCollectNamespacesTask(const TSharedPtr<FGs2FriendDomain>& Self, TFunction<void(TArray<Gs2::Friend::Model::FNamespacePtr>)> OnCollected,const TOptional<FString> NamePrefix) : Self(Self), OnCollected(OnCollected), QueryNamePrefix(NamePrefix) {}
        FCollectNamespacesTask(const FCollectNamespacesTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryNamePrefix(From.QueryNamePrefix) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Friend::Model::FNamespacePtr>>> Result) override
        {
            TArray<Gs2::Friend::Model::FNamespacePtr> Items;
            auto Iterator = Self->Namespaces(QueryNamePrefix)->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Friend::Model::FNamespacePtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FGs2FriendDomain::SubscribeNamespaces(
        TFunction<void(TArray<Gs2::Friend::Model::FNamespacePtr>)> Callback,const TOptional<FString> NamePrefix
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const auto QueryNamePrefix = NamePrefix;
        const auto Parent = Gs2::Friend::Model::Cache::FNamespaceCache::CreateCacheParentKey(
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Friend::Model::FNamespace::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Friend::Model::FNamespacePtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Friend::Model::FNamespace>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, Callback, QueryNamePrefix]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FGs2FriendDomain>(Owner);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectNamespacesTask>>(Domain, Callback, QueryNamePrefix);
                Task->StartBackgroundTask();
            }
        );
    }

    void FGs2FriendDomain::InvalidateNamespaces(const TOptional<FString> NamePrefix)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Friend::Model::FNamespace::TypeName,
            Gs2::Friend::Model::Cache::FNamespaceCache::CreateCacheParentKey(
        TOptional<int32>()
    )
        );
    }

    FGs2FriendDomain::FSubscribeNamespacesWithInitialCallTask::FSubscribeNamespacesWithInitialCallTask(const TSharedPtr<FGs2FriendDomain>& Self, TFunction<void(TArray<Gs2::Friend::Model::FNamespacePtr>)> Callback,const TOptional<FString> NamePrefix) : Self(Self), Callback(Callback), QueryNamePrefix(NamePrefix) {}
    FGs2FriendDomain::FSubscribeNamespacesWithInitialCallTask::FSubscribeNamespacesWithInitialCallTask(const FSubscribeNamespacesWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryNamePrefix(From.QueryNamePrefix) {}
    Gs2::Core::Model::FGs2ErrorPtr FGs2FriendDomain::FSubscribeNamespacesWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectNamespacesTask>>(Self, TFunction<void(TArray<Gs2::Friend::Model::FNamespacePtr>)>(), QueryNamePrefix);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeNamespaces(Callback, QueryNamePrefix);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FGs2FriendDomain::FSubscribeNamespacesWithInitialCallTask>> FGs2FriendDomain::SubscribeNamespacesWithInitialCall(TFunction<void(TArray<Gs2::Friend::Model::FNamespacePtr>)> Callback,const TOptional<FString> NamePrefix)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeNamespacesWithInitialCallTask>>(this->AsShared(), Callback, NamePrefix);
    }

    TSharedPtr<Gs2::Friend::Domain::Model::FNamespaceDomain> FGs2FriendDomain::Namespace(
        const FString NamespaceName
    )
    {
        return MakeShared<Gs2::Friend::Domain::Model::FNamespaceDomain>(
            Gs2,
            AsShared(),
            NamespaceName == TEXT("") ? TOptional<FString>() : TOptional<FString>(NamespaceName)
        );
    }

    void FGs2FriendDomain::UpdateCacheFromStampSheet(
        const FString Method,
        const FString Request,
        const FString Result,
        const TOptional<int32> TimeOffset
    ) {
        if (Method == "UpdateProfileByUserId") {
            TSharedPtr<FJsonObject> RequestModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Request);
                !FJsonSerializer::Deserialize(JsonReader, RequestModelJson))
            {
                return;
            }
            TSharedPtr<FJsonObject> ResultModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Result);
                !FJsonSerializer::Deserialize(JsonReader, ResultModelJson))
            {
                return;
            }
            const auto RequestModel = Gs2::Friend::Request::FUpdateProfileByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Friend::Result::FUpdateProfileByUserIdResult::FromJson(ResultModelJson);

                    if (ResultModel.IsValid() && ResultModel->GetItem() != nullptr)
                    {

                if (!ResultModel.IsValid() || !((ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>())).IsSet())
                    {
                      return;
                      }
                Gs2::Friend::Model::Cache::FProfileCache::Put(
                    Gs2->Cache,

                    RequestModel->GetNamespaceName(),
                    (ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>()),
                    TimeOffset,
                    ResultModel->GetItem()
                );
                    }

        }
    }

    void FGs2FriendDomain::UpdateCacheFromStampTask(
        const FString Method,
        const FString Request,
        const FString Result,
        const TOptional<int32> TimeOffset
    ) {
    }

    void FGs2FriendDomain::UpdateCacheFromJobResult(
        const FString Method,
        const Gs2::JobQueue::Model::FJobPtr Job,
        const Gs2::JobQueue::Model::FJobResultBodyPtr Result,
        const TOptional<int32> TimeOffset
    ) {
        if (Method == "update_profile_by_user_id") {
            TSharedPtr<FJsonObject> RequestModelJson;
            if (!Job->GetArgs().IsSet())
            {
                return;
            }
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(*Job->GetArgs());
                !FJsonSerializer::Deserialize(JsonReader, RequestModelJson))
            {
                return;
            }
            TSharedPtr<FJsonObject> ResultModelJson;
            if (!Result->GetResult().IsSet())
            {
                return;
            }
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(*Result->GetResult());
                !FJsonSerializer::Deserialize(JsonReader, ResultModelJson))
            {
                return;
            }
            const auto RequestModel = Gs2::Friend::Request::FUpdateProfileByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Friend::Result::FUpdateProfileByUserIdResult::FromJson(ResultModelJson);

                    if (ResultModel.IsValid() && ResultModel->GetItem() != nullptr)
                    {

                if (!ResultModel.IsValid() || !((ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>())).IsSet())
                    {
                      return;
                      }
                Gs2::Friend::Model::Cache::FProfileCache::Put(
                    Gs2->Cache,

                    RequestModel->GetNamespaceName(),
                    (ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>()),
                    TimeOffset,
                    ResultModel->GetItem()
                );
                    }

        }
    }

    void FGs2FriendDomain::HandleNotification(
        const FString Action,
        const FString Payload
    ) {
        if (Action == "Follow" || Action == "FollowNotification") {
            TSharedPtr<FJsonObject> PayloadJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Payload);
                !FJsonSerializer::Deserialize(JsonReader, PayloadJson))
            {
                return;
            }
            FollowNotificationEvent.Broadcast(Gs2::Friend::Model::FFollowNotification::FromJson(PayloadJson));
        }
        if (Action == "AcceptRequest" || Action == "AcceptRequestNotification") {
            TSharedPtr<FJsonObject> PayloadJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Payload);
                !FJsonSerializer::Deserialize(JsonReader, PayloadJson))
            {
                return;
            }
            const auto Notification = Gs2::Friend::Model::FAcceptRequestNotification::FromJson(PayloadJson);
            Gs2::Friend::Model::Cache::FSendFriendRequestCache::Delete(
                Gs2->Cache,
                Notification->GetNamespaceName(),
                Notification->GetUserId(),
                Notification->GetTargetUserId(),
                TOptional<int32>()
            );
            Gs2::Friend::Model::Cache::FReceiveFriendRequestCache::Delete(
                Gs2->Cache,
                Notification->GetNamespaceName(),
                Notification->GetTargetUserId(),
                Notification->GetUserId(),
                TOptional<int32>()
            );
            Gs2->Cache->ClearListCache(
                Gs2::Friend::Model::FFriendUser::TypeName,
                Gs2::Friend::Model::Cache::FFriendUserCache::CreateCacheParentKey(
                    Notification->GetNamespaceName(), Notification->GetUserId(), TOptional<bool>(false), TOptional<int32>()
                )
            );
            Gs2->Cache->ClearListCache(
                Gs2::Friend::Model::FFriendUser::TypeName,
                Gs2::Friend::Model::Cache::FFriendUserCache::CreateCacheParentKey(
                    Notification->GetNamespaceName(), Notification->GetUserId(), TOptional<bool>(true), TOptional<int32>()
                )
            );
            Gs2->Cache->ClearListCache(
                Gs2::Friend::Model::FFriendUser::TypeName,
                Gs2::Friend::Model::Cache::FFriendUserCache::CreateCacheParentKey(
                    Notification->GetNamespaceName(), Notification->GetUserId(), TOptional<bool>(), TOptional<int32>()
                )
            );
            Gs2->Cache->ClearListCache(
                Gs2::Friend::Model::FFriendUser::TypeName,
                Gs2::Friend::Model::Cache::FFriendUserCache::CreateCacheParentKey(
                    Notification->GetNamespaceName(), Notification->GetTargetUserId(), TOptional<bool>(false), TOptional<int32>()
                )
            );
            Gs2->Cache->ClearListCache(
                Gs2::Friend::Model::FFriendUser::TypeName,
                Gs2::Friend::Model::Cache::FFriendUserCache::CreateCacheParentKey(
                    Notification->GetNamespaceName(), Notification->GetTargetUserId(), TOptional<bool>(true), TOptional<int32>()
                )
            );
            Gs2->Cache->ClearListCache(
                Gs2::Friend::Model::FFriendUser::TypeName,
                Gs2::Friend::Model::Cache::FFriendUserCache::CreateCacheParentKey(
                    Notification->GetNamespaceName(), Notification->GetTargetUserId(), TOptional<bool>(), TOptional<int32>()
                )
            );
            AcceptRequestNotificationEvent.Broadcast(Notification);
        }
        if (Action == "RejectRequest" || Action == "RejectRequestNotification") {
            TSharedPtr<FJsonObject> PayloadJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Payload);
                !FJsonSerializer::Deserialize(JsonReader, PayloadJson))
            {
                return;
            }
            const auto Notification = Gs2::Friend::Model::FRejectRequestNotification::FromJson(PayloadJson);
            Gs2::Friend::Model::Cache::FSendFriendRequestCache::Delete(
                Gs2->Cache,
                Notification->GetNamespaceName(),
                Notification->GetUserId(),
                Notification->GetTargetUserId(),
                TOptional<int32>()
            );
            Gs2::Friend::Model::Cache::FReceiveFriendRequestCache::Delete(
                Gs2->Cache,
                Notification->GetNamespaceName(),
                Notification->GetTargetUserId(),
                Notification->GetUserId(),
                TOptional<int32>()
            );
            for (const auto& UserId : {Notification->GetUserId(), Notification->GetTargetUserId()})
            {
                for (const auto& WithProfile : {TOptional<bool>(false), TOptional<bool>(true), TOptional<bool>()})
                {
                    Gs2->Cache->ClearListCache(
                        Gs2::Friend::Model::FFriendUser::TypeName,
                        Gs2::Friend::Model::Cache::FFriendUserCache::CreateCacheParentKey(
                            Notification->GetNamespaceName(), UserId, WithProfile, TOptional<int32>()
                        )
                    );
                }
            }
            RejectRequestNotificationEvent.Broadcast(Notification);
        }
        if (Action == "DeleteFriend" || Action == "DeleteFriendNotification") {
            TSharedPtr<FJsonObject> PayloadJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Payload);
                !FJsonSerializer::Deserialize(JsonReader, PayloadJson))
            {
                return;
            }
            const auto Notification = Gs2::Friend::Model::FDeleteFriendNotification::FromJson(PayloadJson);
            for (const auto& WithProfile : {TOptional<bool>(false), TOptional<bool>(true), TOptional<bool>()})
            {
                Gs2->Cache->ClearListCache(
                    Gs2::Friend::Model::FFriendUser::TypeName,
                    Gs2::Friend::Model::Cache::FFriendUserCache::CreateCacheParentKey(
                        Notification->GetNamespaceName(), Notification->GetUserId(), WithProfile, TOptional<int32>()
                    )
                );
            }
            DeleteFriendNotificationEvent.Broadcast(Notification);
        }
        if (Action == "ReceiveRequest" || Action == "ReceiveRequestNotification") {
            TSharedPtr<FJsonObject> PayloadJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Payload);
                !FJsonSerializer::Deserialize(JsonReader, PayloadJson))
            {
                return;
            }
            const auto Notification = Gs2::Friend::Model::FReceiveRequestNotification::FromJson(PayloadJson);
            Gs2->Cache->ClearListCache(
                Gs2::Friend::Model::FSendFriendRequest::TypeName,
                Gs2::Friend::Model::Cache::FSendFriendRequestCache::CreateCacheParentKey(
                    Notification->GetNamespaceName(), Notification->GetFromUserId(), TOptional<int32>()
                )
            );
            Gs2->Cache->ClearListCache(
                Gs2::Friend::Model::FReceiveFriendRequest::TypeName,
                Gs2::Friend::Model::Cache::FReceiveFriendRequestCache::CreateCacheParentKey(
                    Notification->GetNamespaceName(), Notification->GetUserId(), TOptional<int32>()
                )
            );
            for (const auto& UserId : {Notification->GetUserId(), Notification->GetFromUserId()})
            {
                for (const auto& WithProfile : {TOptional<bool>(false), TOptional<bool>(true), TOptional<bool>()})
                {
                    Gs2->Cache->ClearListCache(
                        Gs2::Friend::Model::FFriendUser::TypeName,
                        Gs2::Friend::Model::Cache::FFriendUserCache::CreateCacheParentKey(
                            Notification->GetNamespaceName(), UserId, WithProfile, TOptional<int32>()
                        )
                    );
                }
            }
            ReceiveRequestNotificationEvent.Broadcast(Notification);
        }
        if (Action == "CancelRequest" || Action == "CancelRequestNotification") {
            TSharedPtr<FJsonObject> PayloadJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Payload);
                !FJsonSerializer::Deserialize(JsonReader, PayloadJson))
            {
                return;
            }
            const auto Notification = Gs2::Friend::Model::FCancelRequestNotification::FromJson(PayloadJson);
            Gs2->Cache->ClearListCache(
                Gs2::Friend::Model::FSendFriendRequest::TypeName,
                Gs2::Friend::Model::Cache::FSendFriendRequestCache::CreateCacheParentKey(
                    Notification->GetNamespaceName(), Notification->GetUserId(), TOptional<int32>()
                )
            );
            Gs2->Cache->ClearListCache(
                Gs2::Friend::Model::FReceiveFriendRequest::TypeName,
                Gs2::Friend::Model::Cache::FReceiveFriendRequestCache::CreateCacheParentKey(
                    Notification->GetNamespaceName(), Notification->GetFromUserId(), TOptional<int32>()
                )
            );
            CancelRequestNotificationEvent.Broadcast(Notification);
        }
    }

    FFollowNotificationEvent& FGs2FriendDomain::OnFollowNotification()
    {
        return FollowNotificationEvent;
    }

    FAcceptRequestNotificationEvent& FGs2FriendDomain::OnAcceptRequestNotification()
    {
        return AcceptRequestNotificationEvent;
    }

    FRejectRequestNotificationEvent& FGs2FriendDomain::OnRejectRequestNotification()
    {
        return RejectRequestNotificationEvent;
    }

    FDeleteFriendNotificationEvent& FGs2FriendDomain::OnDeleteFriendNotification()
    {
        return DeleteFriendNotificationEvent;
    }

    FReceiveRequestNotificationEvent& FGs2FriendDomain::OnReceiveRequestNotification()
    {
        return ReceiveRequestNotificationEvent;
    }

    FCancelRequestNotificationEvent& FGs2FriendDomain::OnCancelRequestNotification()
    {
        return CancelRequestNotificationEvent;
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif
