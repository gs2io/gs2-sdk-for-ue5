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

// ReSharper disable CppUnusedIncludeDirective

#include "Guild/Domain/Gs2Guild.h"
#include "Guild/Domain/Model/Namespace.h"
#include "Guild/Domain/Model/GuildModelMaster.h"
#include "Guild/Domain/Model/GuildModel.h"
#include "Guild/Domain/Model/User.h"
#include "Guild/Domain/Model/UserAccessToken.h"
#include "Guild/Domain/Model/Guild.h"
#include "Guild/Domain/Model/JoinedGuild.h"
#include "Guild/Domain/Model/LastGuildMasterActivity.h"
#include "Guild/Domain/Model/CurrentGuildMaster.h"
#include "Guild/Domain/Model/ReceiveMemberRequest.h"
#include "Guild/Domain/Model/SendMemberRequest.h"
#include "Guild/Domain/Model/IgnoreUser.h"
#include "Guild/Model/Cache/ReceiveMemberRequest.h"
#include "Guild/Model/Cache/SendMemberRequest.h"
#include "Guild/Model/Cache/Guild.h"

#include "Guild/Model/Cache/Namespace.h"
#include "Guild/Model/Cache/GuildModelMaster.h"
#include "Guild/Model/Cache/Guild.h"
#include "Guild/Model/Cache/CurrentGuildMaster.h"
#include "Guild/Model/Cache/GuildModel.h"
#include "Guild/Model/Cache/SendMemberRequest.h"
#include "Guild/Model/Cache/JoinedGuild.h"
#include "Guild/Model/Cache/IgnoreUser.h"
#include "Guild/Model/Cache/LastGuildMasterActivity.h"
#include "Guild/Model/Cache/ReceiveMemberRequest.h"

#include "Core/Domain/Gs2.h"

namespace Gs2::Guild::Domain
{

    FGs2GuildDomain::FGs2GuildDomain(
        const Core::Domain::FGs2Ptr& Gs2
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Client(MakeShared<Gs2::Guild::FGs2GuildRestClient>(Gs2->RestSession)),
        ParentKey("guild")
    {
    }

    FGs2GuildDomain::FGs2GuildDomain(
        const FGs2GuildDomain& From
    ):
        Gs2(From.Gs2),
        Client(From.Client),
        ParentKey(From.ParentKey)
    {

    }

    FGs2GuildDomain::FCreateNamespaceTask::FCreateNamespaceTask(
        const TSharedPtr<FGs2GuildDomain>& Self,
        const Request::FCreateNamespaceRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2GuildDomain::FCreateNamespaceTask::FCreateNamespaceTask(
        const FCreateNamespaceTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2GuildDomain::FCreateNamespaceTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Domain::Model::FNamespaceDomain>> Result
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


        Gs2::Guild::Model::Cache::FNamespaceCache::Put(
            Self->Gs2->Cache,

            ResultModel->GetItem()->GetName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        auto Domain = MakeShared<Gs2::Guild::Domain::Model::FNamespaceDomain>(
            Self->Gs2,
            Self,
            ResultModel->GetItem()->GetName()
        );
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGs2GuildDomain::FCreateNamespaceTask>> FGs2GuildDomain::CreateNamespace(
        Request::FCreateNamespaceRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateNamespaceTask>>(this->AsShared(), Request);
    }

    FGs2GuildDomain::FDumpUserDataTask::FDumpUserDataTask(
        const TSharedPtr<FGs2GuildDomain>& Self,
        const Request::FDumpUserDataByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2GuildDomain::FDumpUserDataTask::FDumpUserDataTask(
        const FDumpUserDataTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2GuildDomain::FDumpUserDataTask::Action(
        TSharedPtr<TSharedPtr<FGs2GuildDomain>> Result
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

    TSharedPtr<FAsyncTask<FGs2GuildDomain::FDumpUserDataTask>> FGs2GuildDomain::DumpUserData(
        Request::FDumpUserDataByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDumpUserDataTask>>(this->AsShared(), Request);
    }

    FGs2GuildDomain::FCheckDumpUserDataTask::FCheckDumpUserDataTask(
        const TSharedPtr<FGs2GuildDomain>& Self,
        const Request::FCheckDumpUserDataByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2GuildDomain::FCheckDumpUserDataTask::FCheckDumpUserDataTask(
        const FCheckDumpUserDataTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2GuildDomain::FCheckDumpUserDataTask::Action(
        TSharedPtr<TSharedPtr<FGs2GuildDomain>> Result
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

    TSharedPtr<FAsyncTask<FGs2GuildDomain::FCheckDumpUserDataTask>> FGs2GuildDomain::CheckDumpUserData(
        Request::FCheckDumpUserDataByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCheckDumpUserDataTask>>(this->AsShared(), Request);
    }

    FGs2GuildDomain::FCleanUserDataTask::FCleanUserDataTask(
        const TSharedPtr<FGs2GuildDomain>& Self,
        const Request::FCleanUserDataByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2GuildDomain::FCleanUserDataTask::FCleanUserDataTask(
        const FCleanUserDataTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2GuildDomain::FCleanUserDataTask::Action(
        TSharedPtr<TSharedPtr<FGs2GuildDomain>> Result
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

    TSharedPtr<FAsyncTask<FGs2GuildDomain::FCleanUserDataTask>> FGs2GuildDomain::CleanUserData(
        Request::FCleanUserDataByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCleanUserDataTask>>(this->AsShared(), Request);
    }

    FGs2GuildDomain::FCheckCleanUserDataTask::FCheckCleanUserDataTask(
        const TSharedPtr<FGs2GuildDomain>& Self,
        const Request::FCheckCleanUserDataByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2GuildDomain::FCheckCleanUserDataTask::FCheckCleanUserDataTask(
        const FCheckCleanUserDataTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2GuildDomain::FCheckCleanUserDataTask::Action(
        TSharedPtr<TSharedPtr<FGs2GuildDomain>> Result
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

    TSharedPtr<FAsyncTask<FGs2GuildDomain::FCheckCleanUserDataTask>> FGs2GuildDomain::CheckCleanUserData(
        Request::FCheckCleanUserDataByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCheckCleanUserDataTask>>(this->AsShared(), Request);
    }

    FGs2GuildDomain::FPrepareImportUserDataTask::FPrepareImportUserDataTask(
        const TSharedPtr<FGs2GuildDomain>& Self,
        const Request::FPrepareImportUserDataByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2GuildDomain::FPrepareImportUserDataTask::FPrepareImportUserDataTask(
        const FPrepareImportUserDataTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2GuildDomain::FPrepareImportUserDataTask::Action(
        TSharedPtr<TSharedPtr<FGs2GuildDomain>> Result
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

    TSharedPtr<FAsyncTask<FGs2GuildDomain::FPrepareImportUserDataTask>> FGs2GuildDomain::PrepareImportUserData(
        Request::FPrepareImportUserDataByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FPrepareImportUserDataTask>>(this->AsShared(), Request);
    }

    FGs2GuildDomain::FImportUserDataTask::FImportUserDataTask(
        const TSharedPtr<FGs2GuildDomain>& Self,
        const Request::FImportUserDataByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2GuildDomain::FImportUserDataTask::FImportUserDataTask(
        const FImportUserDataTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2GuildDomain::FImportUserDataTask::Action(
        TSharedPtr<TSharedPtr<FGs2GuildDomain>> Result
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

    TSharedPtr<FAsyncTask<FGs2GuildDomain::FImportUserDataTask>> FGs2GuildDomain::ImportUserData(
        Request::FImportUserDataByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FImportUserDataTask>>(this->AsShared(), Request);
    }

    FGs2GuildDomain::FCheckImportUserDataTask::FCheckImportUserDataTask(
        const TSharedPtr<FGs2GuildDomain>& Self,
        const Request::FCheckImportUserDataByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2GuildDomain::FCheckImportUserDataTask::FCheckImportUserDataTask(
        const FCheckImportUserDataTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2GuildDomain::FCheckImportUserDataTask::Action(
        TSharedPtr<TSharedPtr<FGs2GuildDomain>> Result
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

    TSharedPtr<FAsyncTask<FGs2GuildDomain::FCheckImportUserDataTask>> FGs2GuildDomain::CheckImportUserData(
        Request::FCheckImportUserDataByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCheckImportUserDataTask>>(this->AsShared(), Request);
    }

    Gs2::Guild::Domain::Iterator::FDescribeNamespacesIteratorPtr FGs2GuildDomain::Namespaces(
        const TOptional<FString> NamePrefix
    ) const
    {
        return MakeShared<Gs2::Guild::Domain::Iterator::FDescribeNamespacesIterator>(
            Gs2,
            Client,
            NamePrefix
        );
    }

    Gs2::Core::Domain::CallbackID FGs2GuildDomain::SubscribeNamespaces(
    TFunction<void()> Callback

    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Guild::Model::FNamespace::TypeName,
            Gs2::Guild::Model::Cache::FNamespaceCache::CreateCacheParentKey(
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FGs2GuildDomain::UnsubscribeNamespaces(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Guild::Model::FNamespace::TypeName,
            Gs2::Guild::Model::Cache::FNamespaceCache::CreateCacheParentKey(
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FGs2GuildDomain::FCollectNamespacesTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Guild::Model::FNamespacePtr>>, public TSharedFromThis<FCollectNamespacesTask>
    {
        const TSharedPtr<FGs2GuildDomain> Self;
        const TFunction<void(TArray<Gs2::Guild::Model::FNamespacePtr>)> OnCollected;
    const TOptional<FString> QueryNamePrefix;
    public:
        explicit FCollectNamespacesTask(const TSharedPtr<FGs2GuildDomain>& Self, TFunction<void(TArray<Gs2::Guild::Model::FNamespacePtr>)> OnCollected,const TOptional<FString> NamePrefix) : Self(Self), OnCollected(OnCollected), QueryNamePrefix(NamePrefix) {}
        FCollectNamespacesTask(const FCollectNamespacesTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryNamePrefix(From.QueryNamePrefix) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Guild::Model::FNamespacePtr>>> Result) override
        {
            TArray<Gs2::Guild::Model::FNamespacePtr> Items;
            auto Iterator = Self->Namespaces(QueryNamePrefix)->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Guild::Model::FNamespacePtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FGs2GuildDomain::SubscribeNamespaces(
        TFunction<void(TArray<Gs2::Guild::Model::FNamespacePtr>)> Callback,const TOptional<FString> NamePrefix
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const auto QueryNamePrefix = NamePrefix;
        const auto Parent = Gs2::Guild::Model::Cache::FNamespaceCache::CreateCacheParentKey(
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Guild::Model::FNamespace::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Guild::Model::FNamespacePtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Guild::Model::FNamespace>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, Callback, QueryNamePrefix]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FGs2GuildDomain>(Owner);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectNamespacesTask>>(Domain, Callback, QueryNamePrefix);
                Task->StartBackgroundTask();
            }
        );
    }

    void FGs2GuildDomain::InvalidateNamespaces(const TOptional<FString> NamePrefix)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Guild::Model::FNamespace::TypeName,
            Gs2::Guild::Model::Cache::FNamespaceCache::CreateCacheParentKey(
        TOptional<int32>()
    )
        );
    }

    FGs2GuildDomain::FSubscribeNamespacesWithInitialCallTask::FSubscribeNamespacesWithInitialCallTask(const TSharedPtr<FGs2GuildDomain>& Self, TFunction<void(TArray<Gs2::Guild::Model::FNamespacePtr>)> Callback,const TOptional<FString> NamePrefix) : Self(Self), Callback(Callback), QueryNamePrefix(NamePrefix) {}
    FGs2GuildDomain::FSubscribeNamespacesWithInitialCallTask::FSubscribeNamespacesWithInitialCallTask(const FSubscribeNamespacesWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryNamePrefix(From.QueryNamePrefix) {}
    Gs2::Core::Model::FGs2ErrorPtr FGs2GuildDomain::FSubscribeNamespacesWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectNamespacesTask>>(Self, TFunction<void(TArray<Gs2::Guild::Model::FNamespacePtr>)>(), QueryNamePrefix);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeNamespaces(Callback, QueryNamePrefix);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FGs2GuildDomain::FSubscribeNamespacesWithInitialCallTask>> FGs2GuildDomain::SubscribeNamespacesWithInitialCall(TFunction<void(TArray<Gs2::Guild::Model::FNamespacePtr>)> Callback,const TOptional<FString> NamePrefix)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeNamespacesWithInitialCallTask>>(this->AsShared(), Callback, NamePrefix);
    }

    TSharedPtr<Gs2::Guild::Domain::Model::FNamespaceDomain> FGs2GuildDomain::Namespace(
        const FString NamespaceName
    )
    {
        return MakeShared<Gs2::Guild::Domain::Model::FNamespaceDomain>(
            Gs2,
            AsShared(),
            NamespaceName == TEXT("") ? TOptional<FString>() : TOptional<FString>(NamespaceName)
        );
    }

    void FGs2GuildDomain::UpdateCacheFromStampSheet(
        const FString Method,
        const FString Request,
        const FString Result,
        const TOptional<int32> TimeOffset
    ) {
        if (Method == "IncreaseMaximumCurrentMaximumMemberCountByGuildName") {
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
            const auto RequestModel = Gs2::Guild::Request::FIncreaseMaximumCurrentMaximumMemberCountByGuildNameRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Guild::Result::FIncreaseMaximumCurrentMaximumMemberCountByGuildNameResult::FromJson(ResultModelJson);

                    if (ResultModel.IsValid() && ResultModel->GetItem() != nullptr)
                    {

                if (!ResultModel.IsValid() || !ResultModel->GetItem().IsValid())
                    {
                      return;
                      }
                Gs2::Guild::Model::Cache::FGuildCache::Put(
                    Gs2->Cache,

                    RequestModel->GetNamespaceName(),
                    ResultModel->GetItem()->GetGuildModelName(),
                    RequestModel->GetGuildName(),
                    TimeOffset,
                    ResultModel->GetItem()
                );
                    }

        }
        if (Method == "SetMaximumCurrentMaximumMemberCountByGuildName") {
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
            const auto RequestModel = Gs2::Guild::Request::FSetMaximumCurrentMaximumMemberCountByGuildNameRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Guild::Result::FSetMaximumCurrentMaximumMemberCountByGuildNameResult::FromJson(ResultModelJson);

                    if (ResultModel.IsValid() && ResultModel->GetItem() != nullptr)
                    {

                if (!ResultModel.IsValid() || !ResultModel->GetItem().IsValid())
                    {
                      return;
                      }
                Gs2::Guild::Model::Cache::FGuildCache::Put(
                    Gs2->Cache,

                    RequestModel->GetNamespaceName(),
                    ResultModel->GetItem()->GetGuildModelName(),
                    RequestModel->GetGuildName(),
                    TimeOffset,
                    ResultModel->GetItem()
                );
                    }

        }
    }

    void FGs2GuildDomain::UpdateCacheFromStampTask(
        const FString Method,
        const FString Request,
        const FString Result,
        const TOptional<int32> TimeOffset
    ) {
        if (Method == "DecreaseMaximumCurrentMaximumMemberCountByGuildName") {
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
            const auto RequestModel = Gs2::Guild::Request::FDecreaseMaximumCurrentMaximumMemberCountByGuildNameRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Guild::Result::FDecreaseMaximumCurrentMaximumMemberCountByGuildNameResult::FromJson(ResultModelJson);

                    if (ResultModel.IsValid() && ResultModel->GetItem() != nullptr)
                    {

                if (!ResultModel.IsValid() || !ResultModel->GetItem().IsValid())
                    {
                      return;
                      }
                Gs2::Guild::Model::Cache::FGuildCache::Put(
                    Gs2->Cache,

                    RequestModel->GetNamespaceName(),
                    ResultModel->GetItem()->GetGuildModelName(),
                    RequestModel->GetGuildName(),
                    TimeOffset,
                    ResultModel->GetItem()
                );
                    }

        }
    }

    void FGs2GuildDomain::UpdateCacheFromJobResult(
        const FString Method,
        const Gs2::JobQueue::Model::FJobPtr Job,
        const Gs2::JobQueue::Model::FJobResultBodyPtr Result,
        const TOptional<int32> TimeOffset
    ) {
        if (Method == "increase_maximum_current_maximum_member_count_by_guild_name") {
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
            const auto RequestModel = Gs2::Guild::Request::FIncreaseMaximumCurrentMaximumMemberCountByGuildNameRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Guild::Result::FIncreaseMaximumCurrentMaximumMemberCountByGuildNameResult::FromJson(ResultModelJson);

                    if (ResultModel.IsValid() && ResultModel->GetItem() != nullptr)
                    {

                if (!ResultModel.IsValid() || !ResultModel->GetItem().IsValid())
                    {
                      return;
                      }
                Gs2::Guild::Model::Cache::FGuildCache::Put(
                    Gs2->Cache,

                    RequestModel->GetNamespaceName(),
                    ResultModel->GetItem()->GetGuildModelName(),
                    RequestModel->GetGuildName(),
                    TimeOffset,
                    ResultModel->GetItem()
                );
                    }

        }
        if (Method == "set_maximum_current_maximum_member_count_by_guild_name") {
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
            const auto RequestModel = Gs2::Guild::Request::FSetMaximumCurrentMaximumMemberCountByGuildNameRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Guild::Result::FSetMaximumCurrentMaximumMemberCountByGuildNameResult::FromJson(ResultModelJson);

                    if (ResultModel.IsValid() && ResultModel->GetItem() != nullptr)
                    {

                if (!ResultModel.IsValid() || !ResultModel->GetItem().IsValid())
                    {
                      return;
                      }
                Gs2::Guild::Model::Cache::FGuildCache::Put(
                    Gs2->Cache,

                    RequestModel->GetNamespaceName(),
                    ResultModel->GetItem()->GetGuildModelName(),
                    RequestModel->GetGuildName(),
                    TimeOffset,
                    ResultModel->GetItem()
                );
                    }

        }
    }

    void FGs2GuildDomain::HandleNotification(
        const FString Action,
        const FString Payload
    ) {
        if (Action == "ReceiveRequestNotification") {
            TSharedPtr<FJsonObject> PayloadJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Payload);
                !FJsonSerializer::Deserialize(JsonReader, PayloadJson))
            {
                return;
            }
            const auto ListParentKey = Gs2::Guild::Domain::Model::FGuildDomain::CreateCacheParentKey(
                PayloadJson->GetStringField(ANSI_TO_TCHAR("namespaceName")),
                PayloadJson->GetStringField(ANSI_TO_TCHAR("guildModelName")),
                PayloadJson->GetStringField(ANSI_TO_TCHAR("guildName")),
                "ReceiveMemberRequest"
            );
            Gs2->Cache->ClearListCache(Gs2::Guild::Model::FReceiveMemberRequest::TypeName, ListParentKey);
            ReceiveRequestNotificationEvent.Broadcast(Gs2::Guild::Model::FReceiveRequestNotification::FromJson(PayloadJson));
        }
        if (Action == "RemoveRequestNotification") {
            TSharedPtr<FJsonObject> PayloadJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Payload);
                !FJsonSerializer::Deserialize(JsonReader, PayloadJson))
            {
                return;
            }
            {
                Gs2::Guild::Model::Cache::FReceiveMemberRequestCache::Delete(
                    Gs2->Cache,
                    PayloadJson->GetStringField(ANSI_TO_TCHAR("namespaceName")),
                    PayloadJson->GetStringField(ANSI_TO_TCHAR("guildModelName")),
                    PayloadJson->GetStringField(ANSI_TO_TCHAR("guildName")),
                    PayloadJson->GetStringField(ANSI_TO_TCHAR("fromUserId")),
                    TOptional<int32>()
                );
                Gs2->Cache->ClearListCache(
                    Gs2::Guild::Model::FReceiveMemberRequest::TypeName,
                    Gs2::Guild::Model::Cache::FReceiveMemberRequestCache::CreateCacheParentKey(
                        PayloadJson->GetStringField(ANSI_TO_TCHAR("namespaceName")),
                        PayloadJson->GetStringField(ANSI_TO_TCHAR("guildModelName")),
                        PayloadJson->GetStringField(ANSI_TO_TCHAR("guildName")),
                        TOptional<int32>()
                    )
                );
            }
            {
                Gs2::Guild::Model::Cache::FSendMemberRequestCache::Delete(
                    Gs2->Cache,
                    PayloadJson->GetStringField(ANSI_TO_TCHAR("namespaceName")),
                    PayloadJson->GetStringField(ANSI_TO_TCHAR("fromUserId")),
                    PayloadJson->GetStringField(ANSI_TO_TCHAR("guildModelName")),
                    PayloadJson->GetStringField(ANSI_TO_TCHAR("guildName")),
                    TOptional<int32>()
                );
                Gs2->Cache->ClearListCache(
                    Gs2::Guild::Model::FSendMemberRequest::TypeName,
                    Gs2::Guild::Model::Cache::FSendMemberRequestCache::CreateCacheParentKey(
                        PayloadJson->GetStringField(ANSI_TO_TCHAR("namespaceName")),
                        PayloadJson->GetStringField(ANSI_TO_TCHAR("guildModelName")),
                        PayloadJson->GetStringField(ANSI_TO_TCHAR("fromUserId")),
                        TOptional<int32>()
                    )
                );
            }
            RemoveRequestNotificationEvent.Broadcast(Gs2::Guild::Model::FRemoveRequestNotification::FromJson(PayloadJson));
        }
        if (Action == "ChangeNotification") {
            TSharedPtr<FJsonObject> PayloadJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Payload);
                !FJsonSerializer::Deserialize(JsonReader, PayloadJson))
            {
                return;
            }
            ChangeNotificationEvent.Broadcast(Gs2::Guild::Model::FChangeNotification::FromJson(PayloadJson));
        }
        if (Action == "JoinNotification") {
            TSharedPtr<FJsonObject> PayloadJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Payload);
                !FJsonSerializer::Deserialize(JsonReader, PayloadJson))
            {
                return;
            }
            {
                const auto ParentKey = Gs2::Guild::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    PayloadJson->GetStringField(ANSI_TO_TCHAR("namespaceName")),
                    "Guild"
                );
                const auto Key = Gs2::Guild::Domain::Model::FGuildDomain::CreateCacheKey(
                    PayloadJson->GetStringField(ANSI_TO_TCHAR("guildModelName")),
                    PayloadJson->GetStringField(ANSI_TO_TCHAR("guildName"))
                );
                Gs2->Cache->Delete(Gs2::Guild::Model::FGuild::TypeName, ParentKey, Key);
            }
            JoinNotificationEvent.Broadcast(Gs2::Guild::Model::FJoinNotification::FromJson(PayloadJson));
        }
        if (Action == "LeaveNotification") {
            TSharedPtr<FJsonObject> PayloadJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Payload);
                !FJsonSerializer::Deserialize(JsonReader, PayloadJson))
            {
                return;
            }
            {
                const auto ParentKey = Gs2::Guild::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    PayloadJson->GetStringField(ANSI_TO_TCHAR("namespaceName")),
                    "Guild"
                );
                const auto Key = Gs2::Guild::Domain::Model::FGuildDomain::CreateCacheKey(
                    PayloadJson->GetStringField(ANSI_TO_TCHAR("guildModelName")),
                    PayloadJson->GetStringField(ANSI_TO_TCHAR("guildName"))
                );
                Gs2->Cache->Delete(Gs2::Guild::Model::FGuild::TypeName, ParentKey, Key);
            }
            LeaveNotificationEvent.Broadcast(Gs2::Guild::Model::FLeaveNotification::FromJson(PayloadJson));
        }
        if (Action == "ChangeMemberNotification") {
            TSharedPtr<FJsonObject> PayloadJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Payload);
                !FJsonSerializer::Deserialize(JsonReader, PayloadJson))
            {
                return;
            }
            {
                const auto ParentKey = Gs2::Guild::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    PayloadJson->GetStringField(ANSI_TO_TCHAR("namespaceName")),
                    "Guild"
                );
                const auto Key = Gs2::Guild::Domain::Model::FGuildDomain::CreateCacheKey(
                    PayloadJson->GetStringField(ANSI_TO_TCHAR("guildModelName")),
                    PayloadJson->GetStringField(ANSI_TO_TCHAR("guildName"))
                );
                Gs2->Cache->Delete(Gs2::Guild::Model::FGuild::TypeName, ParentKey, Key);
            }
            ChangeMemberNotificationEvent.Broadcast(Gs2::Guild::Model::FChangeMemberNotification::FromJson(PayloadJson));
        }
    }

    FReceiveRequestNotificationEvent& FGs2GuildDomain::OnReceiveRequestNotification()
    {
        return ReceiveRequestNotificationEvent;
    }

    FRemoveRequestNotificationEvent& FGs2GuildDomain::OnRemoveRequestNotification()
    {
        return RemoveRequestNotificationEvent;
    }

    FChangeNotificationEvent& FGs2GuildDomain::OnChangeNotification()
    {
        return ChangeNotificationEvent;
    }

    FJoinNotificationEvent& FGs2GuildDomain::OnJoinNotification()
    {
        return JoinNotificationEvent;
    }

    FLeaveNotificationEvent& FGs2GuildDomain::OnLeaveNotification()
    {
        return LeaveNotificationEvent;
    }

    FChangeMemberNotificationEvent& FGs2GuildDomain::OnChangeMemberNotification()
    {
        return ChangeMemberNotificationEvent;
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif
