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

#include "Guild/Domain/Model/Namespace.h"
#include "Guild/Domain/Model/Namespace.h"
#include "Guild/Domain/Model/GuildModelMaster.h"
#include "Guild/Domain/Model/GuildModel.h"
#include "Guild/Domain/Model/User.h"
#include "Guild/Domain/Model/UserAccessToken.h"
#include "Guild/Domain/Model/Guild.h"
#include "Guild/Domain/Model/JoinedGuild.h"
#include "Guild/Domain/Model/JoinedGuildAccessToken.h"
#include "Guild/Domain/Model/LastGuildMasterActivity.h"
#include "Guild/Domain/Model/CurrentGuildMaster.h"
#include "Guild/Domain/Model/ReceiveMemberRequest.h"
#include "Guild/Domain/Model/SendMemberRequest.h"
#include "Guild/Domain/Model/SendMemberRequestAccessToken.h"
#include "Guild/Domain/Model/IgnoreUser.h"

#include "Guild/Model/Cache/GuildModelMaster.h"
#include "Guild/Model/Cache/GuildModel.h"
#include "Guild/Model/Cache/Guild.h"
#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"
#include "Guild/Domain/Model/GuildAccessToken.h"

namespace Gs2::Guild::Domain::Model
{

    FNamespaceDomain::FNamespaceDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Guild::Domain::FGs2GuildDomainPtr& Service,
        const TOptional<FString> NamespaceName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Guild::FGs2GuildRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        ParentKey("guild:Namespace")
    {
    }

    FNamespaceDomain::FNamespaceDomain(
        const FNamespaceDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        ParentKey(From.ParentKey)
    {

    }

    FNamespaceDomain::FGetStatusTask::FGetStatusTask(
        const TSharedPtr<FNamespaceDomain>& Self,
        const Request::FGetNamespaceStatusRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FGetStatusTask::FGetStatusTask(
        const FGetStatusTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FGetStatusTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Domain::Model::FNamespaceDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->GetNamespaceStatus(
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
            if (ResultModel->GetStatus().IsSet())
            {
                Self->Status = Domain->Status = ResultModel->GetStatus();
            }
        }
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FGetStatusTask>> FNamespaceDomain::GetStatus(
        Request::FGetNamespaceStatusRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetStatusTask>>(this->AsShared(), Request);
    }

    FNamespaceDomain::FGetTask::FGetTask(
        const TSharedPtr<FNamespaceDomain>& Self,
        const Request::FGetNamespaceRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Model::FNamespace>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->GetNamespace(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FGetTask>> FNamespaceDomain::Get(
        Request::FGetNamespaceRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FNamespaceDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FNamespaceDomain>& Self,
        const Request::FUpdateNamespaceRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Domain::Model::FNamespaceDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->UpdateNamespace(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel->GetItem() != nullptr)
        {
            const auto Key = Gs2::Guild::Domain::Model::FNamespaceDomain::CreateCacheKey(
                ResultModel->GetItem()->GetName()
            );
            Self->Gs2->Cache->Put(
                Gs2::Guild::Model::FNamespace::TypeName,
                "guild:Namespace",
                Key,
                ResultModel->GetItem(),
                FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
            );
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FUpdateTask>> FNamespaceDomain::Update(
        Request::FUpdateNamespaceRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FNamespaceDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FNamespaceDomain>& Self,
        const Request::FDeleteNamespaceRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Domain::Model::FNamespaceDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->DeleteNamespace(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FDeleteTask>> FNamespaceDomain::Delete(
        Request::FDeleteNamespaceRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FNamespaceDomain::FCreateGuildModelMasterTask::FCreateGuildModelMasterTask(
        const TSharedPtr<FNamespaceDomain>& Self,
        const Request::FCreateGuildModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FCreateGuildModelMasterTask::FCreateGuildModelMasterTask(
        const FCreateGuildModelMasterTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FCreateGuildModelMasterTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Domain::Model::FGuildModelMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->CreateGuildModelMaster(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        auto Domain = MakeShared<Gs2::Guild::Domain::Model::FGuildModelMasterDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetName()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FCreateGuildModelMasterTask>> FNamespaceDomain::CreateGuildModelMaster(
        Request::FCreateGuildModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateGuildModelMasterTask>>(this->AsShared(), Request);
    }

    TSharedPtr<Gs2::Guild::Domain::Model::FCurrentGuildMasterDomain> FNamespaceDomain::CurrentGuildMaster(
    )
    {
        return MakeShared<Gs2::Guild::Domain::Model::FCurrentGuildMasterDomain>(
            Gs2,
            Service,
            NamespaceName
        );
    }

    Gs2::Guild::Domain::Iterator::FDescribeGuildModelsIteratorPtr FNamespaceDomain::GuildModels(
    ) const
    {
        return MakeShared<Gs2::Guild::Domain::Iterator::FDescribeGuildModelsIterator>(
            Gs2,
            Client,
            NamespaceName
        );
    }

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeGuildModels(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Guild::Model::FGuildModel::TypeName,
            Gs2::Guild::Model::Cache::FGuildModelCache::CreateCacheParentKey(
                NamespaceName,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FNamespaceDomain::UnsubscribeGuildModels(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Guild::Model::FGuildModel::TypeName,
            Gs2::Guild::Model::Cache::FGuildModelCache::CreateCacheParentKey(
                NamespaceName,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FNamespaceDomain::FCollectGuildModelsTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Guild::Model::FGuildModelPtr>>, public TSharedFromThis<FCollectGuildModelsTask>
    {
        const TSharedPtr<FNamespaceDomain> Self;
        const TFunction<void(TArray<Gs2::Guild::Model::FGuildModelPtr>)> OnCollected;

    public:
        explicit FCollectGuildModelsTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Guild::Model::FGuildModelPtr>)> OnCollected) : Self(Self), OnCollected(OnCollected) {}
        FCollectGuildModelsTask(const FCollectGuildModelsTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Guild::Model::FGuildModelPtr>>> Result) override
        {
            TArray<Gs2::Guild::Model::FGuildModelPtr> Items;
            auto Iterator = Self->GuildModels()->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Guild::Model::FGuildModelPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeGuildModels(
        TFunction<void(TArray<Gs2::Guild::Model::FGuildModelPtr>)> Callback
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Guild::Domain::FGs2GuildDomain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto Parent = Gs2::Guild::Model::Cache::FGuildModelCache::CreateCacheParentKey(
        NamespaceName,
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Guild::Model::FGuildModel::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Guild::Model::FGuildModelPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Guild::Model::FGuildModel>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FNamespaceDomain>(Owner, WeakService.Pin(), QueryNamespaceName);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectGuildModelsTask>>(Domain, Callback);
                Task->StartBackgroundTask();
            }
        );
    }

    void FNamespaceDomain::InvalidateGuildModels()
    {
        Gs2->Cache->ClearListCache(
            Gs2::Guild::Model::FGuildModel::TypeName,
            Gs2::Guild::Model::Cache::FGuildModelCache::CreateCacheParentKey(
        NamespaceName,
        TOptional<int32>()
    )
        );
    }

    FNamespaceDomain::FSubscribeGuildModelsWithInitialCallTask::FSubscribeGuildModelsWithInitialCallTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Guild::Model::FGuildModelPtr>)> Callback) : Self(Self), Callback(Callback) {}
    FNamespaceDomain::FSubscribeGuildModelsWithInitialCallTask::FSubscribeGuildModelsWithInitialCallTask(const FSubscribeGuildModelsWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback) {}
    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FSubscribeGuildModelsWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectGuildModelsTask>>(Self, TFunction<void(TArray<Gs2::Guild::Model::FGuildModelPtr>)>());
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeGuildModels(Callback);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FNamespaceDomain::FSubscribeGuildModelsWithInitialCallTask>> FNamespaceDomain::SubscribeGuildModelsWithInitialCall(TFunction<void(TArray<Gs2::Guild::Model::FGuildModelPtr>)> Callback)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeGuildModelsWithInitialCallTask>>(this->AsShared(), Callback);
    }

    TSharedPtr<Gs2::Guild::Domain::Model::FGuildModelDomain> FNamespaceDomain::GuildModel(
        const FString GuildModelName
    )
    {
        return MakeShared<Gs2::Guild::Domain::Model::FGuildModelDomain>(
            Gs2,
            Service,
            NamespaceName,
            GuildModelName == TEXT("") ? TOptional<FString>() : TOptional<FString>(GuildModelName)
        );
    }

    Gs2::Guild::Domain::Iterator::FDescribeGuildModelMastersIteratorPtr FNamespaceDomain::GuildModelMasters(
        const TOptional<FString> NamePrefix
    ) const
    {
        return MakeShared<Gs2::Guild::Domain::Iterator::FDescribeGuildModelMastersIterator>(
            Gs2,
            Client,
            NamespaceName,
            NamePrefix
        );
    }

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeGuildModelMasters(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Guild::Model::FGuildModelMaster::TypeName,
            Gs2::Guild::Model::Cache::FGuildModelMasterCache::CreateCacheParentKey(
                NamespaceName,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FNamespaceDomain::UnsubscribeGuildModelMasters(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Guild::Model::FGuildModelMaster::TypeName,
            Gs2::Guild::Model::Cache::FGuildModelMasterCache::CreateCacheParentKey(
                NamespaceName,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FNamespaceDomain::FCollectGuildModelMastersTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Guild::Model::FGuildModelMasterPtr>>, public TSharedFromThis<FCollectGuildModelMastersTask>
    {
        const TSharedPtr<FNamespaceDomain> Self;
        const TFunction<void(TArray<Gs2::Guild::Model::FGuildModelMasterPtr>)> OnCollected;
    const TOptional<FString> QueryNamePrefix;
    public:
        explicit FCollectGuildModelMastersTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Guild::Model::FGuildModelMasterPtr>)> OnCollected,const TOptional<FString> NamePrefix) : Self(Self), OnCollected(OnCollected), QueryNamePrefix(NamePrefix) {}
        FCollectGuildModelMastersTask(const FCollectGuildModelMastersTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryNamePrefix(From.QueryNamePrefix) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Guild::Model::FGuildModelMasterPtr>>> Result) override
        {
            TArray<Gs2::Guild::Model::FGuildModelMasterPtr> Items;
            auto Iterator = Self->GuildModelMasters(QueryNamePrefix)->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Guild::Model::FGuildModelMasterPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeGuildModelMasters(
        TFunction<void(TArray<Gs2::Guild::Model::FGuildModelMasterPtr>)> Callback,const TOptional<FString> NamePrefix
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Guild::Domain::FGs2GuildDomain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryNamePrefix = NamePrefix;
        const auto Parent = Gs2::Guild::Model::Cache::FGuildModelMasterCache::CreateCacheParentKey(
        NamespaceName,
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Guild::Model::FGuildModelMaster::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Guild::Model::FGuildModelMasterPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Guild::Model::FGuildModelMaster>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryNamePrefix]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FNamespaceDomain>(Owner, WeakService.Pin(), QueryNamespaceName);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectGuildModelMastersTask>>(Domain, Callback, QueryNamePrefix);
                Task->StartBackgroundTask();
            }
        );
    }

    void FNamespaceDomain::InvalidateGuildModelMasters(const TOptional<FString> NamePrefix)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Guild::Model::FGuildModelMaster::TypeName,
            Gs2::Guild::Model::Cache::FGuildModelMasterCache::CreateCacheParentKey(
        NamespaceName,
        TOptional<int32>()
    )
        );
    }

    FNamespaceDomain::FSubscribeGuildModelMastersWithInitialCallTask::FSubscribeGuildModelMastersWithInitialCallTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Guild::Model::FGuildModelMasterPtr>)> Callback,const TOptional<FString> NamePrefix) : Self(Self), Callback(Callback), QueryNamePrefix(NamePrefix) {}
    FNamespaceDomain::FSubscribeGuildModelMastersWithInitialCallTask::FSubscribeGuildModelMastersWithInitialCallTask(const FSubscribeGuildModelMastersWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryNamePrefix(From.QueryNamePrefix) {}
    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FSubscribeGuildModelMastersWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectGuildModelMastersTask>>(Self, TFunction<void(TArray<Gs2::Guild::Model::FGuildModelMasterPtr>)>(), QueryNamePrefix);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeGuildModelMasters(Callback, QueryNamePrefix);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FNamespaceDomain::FSubscribeGuildModelMastersWithInitialCallTask>> FNamespaceDomain::SubscribeGuildModelMastersWithInitialCall(TFunction<void(TArray<Gs2::Guild::Model::FGuildModelMasterPtr>)> Callback,const TOptional<FString> NamePrefix)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeGuildModelMastersWithInitialCallTask>>(this->AsShared(), Callback, NamePrefix);
    }

    TSharedPtr<Gs2::Guild::Domain::Model::FGuildModelMasterDomain> FNamespaceDomain::GuildModelMaster(
        const FString GuildModelName
    )
    {
        return MakeShared<Gs2::Guild::Domain::Model::FGuildModelMasterDomain>(
            Gs2,
            Service,
            NamespaceName,
            GuildModelName == TEXT("") ? TOptional<FString>() : TOptional<FString>(GuildModelName)
        );
    }

    Gs2::Guild::Domain::Iterator::FSearchGuildsByUserIdIteratorPtr FNamespaceDomain::SearchGuilds(
        const FString GuildModelName,
        const FString UserId,
        const TOptional<FString> DisplayName,
        const TSharedPtr<TArray<int32>> Attributes1,
        const TSharedPtr<TArray<int32>> Attributes2,
        const TSharedPtr<TArray<int32>> Attributes3,
        const TSharedPtr<TArray<int32>> Attributes4,
        const TSharedPtr<TArray<int32>> Attributes5,
        const TSharedPtr<TArray<FString>> JoinPolicies,
        const TOptional<bool> IncludeFullMembersGuild,
        const TOptional<FString> OrderBy,
        const TOptional<FString> TimeOffsetToken
    ) const
    {
        return MakeShared<Gs2::Guild::Domain::Iterator::FSearchGuildsByUserIdIterator>(
            Gs2,
            Client,
            NamespaceName,
            GuildModelName,
            UserId,
            DisplayName,
            Attributes1,
            Attributes2,
            Attributes3,
            Attributes4,
            Attributes5,
            JoinPolicies,
            IncludeFullMembersGuild,
            OrderBy,
            TimeOffsetToken
        );
    }

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeSearchGuilds(
     const FString GuildModelName, TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Guild::Model::FGuild::TypeName,
            Gs2::Guild::Model::Cache::FGuildCache::CreateCacheParentKey(
                NamespaceName,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FNamespaceDomain::UnsubscribeSearchGuilds(
        const FString GuildModelName
        , Gs2::Core::Domain::CallbackID CallbackID, const FString UserId, const TOptional<FString> DisplayName, const TSharedPtr<TArray<int32>> Attributes1, const TSharedPtr<TArray<int32>> Attributes2, const TSharedPtr<TArray<int32>> Attributes3, const TSharedPtr<TArray<int32>> Attributes4, const TSharedPtr<TArray<int32>> Attributes5, const TSharedPtr<TArray<FString>> JoinPolicies, const TOptional<bool> IncludeFullMembersGuild, const TOptional<FString> OrderBy, const TOptional<FString> TimeOffsetToken
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Guild::Model::FGuild::TypeName,
            Gs2::Guild::Model::Cache::FGuildCache::CreateCacheParentKey(
                NamespaceName,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FNamespaceDomain::FCollectSearchGuildsTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Guild::Model::FGuildPtr>>, public TSharedFromThis<FCollectSearchGuildsTask>
    {
        const TSharedPtr<FNamespaceDomain> Self;
        const TFunction<void(TArray<Gs2::Guild::Model::FGuildPtr>)> OnCollected;
    const FString QueryGuildModelName;const FString QueryUserId;const TOptional<FString> QueryDisplayName;const TSharedPtr<TArray<int32>> QueryAttributes1;const TSharedPtr<TArray<int32>> QueryAttributes2;const TSharedPtr<TArray<int32>> QueryAttributes3;const TSharedPtr<TArray<int32>> QueryAttributes4;const TSharedPtr<TArray<int32>> QueryAttributes5;const TSharedPtr<TArray<FString>> QueryJoinPolicies;const TOptional<bool> QueryIncludeFullMembersGuild;const TOptional<FString> QueryOrderBy;const TOptional<FString> QueryTimeOffsetToken;
    public:
        explicit FCollectSearchGuildsTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Guild::Model::FGuildPtr>)> OnCollected,const FString GuildModelName,const FString UserId,const TOptional<FString> DisplayName,const TSharedPtr<TArray<int32>> Attributes1,const TSharedPtr<TArray<int32>> Attributes2,const TSharedPtr<TArray<int32>> Attributes3,const TSharedPtr<TArray<int32>> Attributes4,const TSharedPtr<TArray<int32>> Attributes5,const TSharedPtr<TArray<FString>> JoinPolicies,const TOptional<bool> IncludeFullMembersGuild,const TOptional<FString> OrderBy,const TOptional<FString> TimeOffsetToken) : Self(Self), OnCollected(OnCollected), QueryGuildModelName(GuildModelName), QueryUserId(UserId), QueryDisplayName(DisplayName), QueryAttributes1(Attributes1), QueryAttributes2(Attributes2), QueryAttributes3(Attributes3), QueryAttributes4(Attributes4), QueryAttributes5(Attributes5), QueryJoinPolicies(JoinPolicies), QueryIncludeFullMembersGuild(IncludeFullMembersGuild), QueryOrderBy(OrderBy), QueryTimeOffsetToken(TimeOffsetToken) {}
        FCollectSearchGuildsTask(const FCollectSearchGuildsTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryGuildModelName(From.QueryGuildModelName), QueryUserId(From.QueryUserId), QueryDisplayName(From.QueryDisplayName), QueryAttributes1(From.QueryAttributes1), QueryAttributes2(From.QueryAttributes2), QueryAttributes3(From.QueryAttributes3), QueryAttributes4(From.QueryAttributes4), QueryAttributes5(From.QueryAttributes5), QueryJoinPolicies(From.QueryJoinPolicies), QueryIncludeFullMembersGuild(From.QueryIncludeFullMembersGuild), QueryOrderBy(From.QueryOrderBy), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Guild::Model::FGuildPtr>>> Result) override
        {
            TArray<Gs2::Guild::Model::FGuildPtr> Items;
            auto Iterator = Self->SearchGuilds(QueryGuildModelName, QueryUserId, QueryDisplayName, QueryAttributes1, QueryAttributes2, QueryAttributes3, QueryAttributes4, QueryAttributes5, QueryJoinPolicies, QueryIncludeFullMembersGuild, QueryOrderBy, QueryTimeOffsetToken)->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Guild::Model::FGuildPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeSearchGuilds(
        TFunction<void(TArray<Gs2::Guild::Model::FGuildPtr>)> Callback,const FString GuildModelName,const FString UserId,const TOptional<FString> DisplayName,const TSharedPtr<TArray<int32>> Attributes1,const TSharedPtr<TArray<int32>> Attributes2,const TSharedPtr<TArray<int32>> Attributes3,const TSharedPtr<TArray<int32>> Attributes4,const TSharedPtr<TArray<int32>> Attributes5,const TSharedPtr<TArray<FString>> JoinPolicies,const TOptional<bool> IncludeFullMembersGuild,const TOptional<FString> OrderBy,const TOptional<FString> TimeOffsetToken
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Guild::Domain::FGs2GuildDomain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryGuildModelName = GuildModelName;
        const auto QueryUserId = UserId;
        const auto QueryDisplayName = DisplayName;
        const auto QueryAttributes1 = Attributes1;
        const auto QueryAttributes2 = Attributes2;
        const auto QueryAttributes3 = Attributes3;
        const auto QueryAttributes4 = Attributes4;
        const auto QueryAttributes5 = Attributes5;
        const auto QueryJoinPolicies = JoinPolicies;
        const auto QueryIncludeFullMembersGuild = IncludeFullMembersGuild;
        const auto QueryOrderBy = OrderBy;
        const auto QueryTimeOffsetToken = TimeOffsetToken;
        const auto Parent = Gs2::Guild::Model::Cache::FGuildCache::CreateCacheParentKey(
        NamespaceName,
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Guild::Model::FGuild::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Guild::Model::FGuildPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Guild::Model::FGuild>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryGuildModelName, QueryUserId, QueryDisplayName, QueryAttributes1, QueryAttributes2, QueryAttributes3, QueryAttributes4, QueryAttributes5, QueryJoinPolicies, QueryIncludeFullMembersGuild, QueryOrderBy, QueryTimeOffsetToken]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FNamespaceDomain>(Owner, WeakService.Pin(), QueryNamespaceName);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectSearchGuildsTask>>(Domain, Callback, QueryGuildModelName, QueryUserId, QueryDisplayName, QueryAttributes1, QueryAttributes2, QueryAttributes3, QueryAttributes4, QueryAttributes5, QueryJoinPolicies, QueryIncludeFullMembersGuild, QueryOrderBy, QueryTimeOffsetToken);
                Task->StartBackgroundTask();
            }
        );
    }

    void FNamespaceDomain::InvalidateSearchGuilds(const FString GuildModelName,const FString UserId,const TOptional<FString> DisplayName,const TSharedPtr<TArray<int32>> Attributes1,const TSharedPtr<TArray<int32>> Attributes2,const TSharedPtr<TArray<int32>> Attributes3,const TSharedPtr<TArray<int32>> Attributes4,const TSharedPtr<TArray<int32>> Attributes5,const TSharedPtr<TArray<FString>> JoinPolicies,const TOptional<bool> IncludeFullMembersGuild,const TOptional<FString> OrderBy,const TOptional<FString> TimeOffsetToken)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Guild::Model::FGuild::TypeName,
            Gs2::Guild::Model::Cache::FGuildCache::CreateCacheParentKey(
        NamespaceName,
        TOptional<int32>()
    )
        );
    }

    FNamespaceDomain::FSubscribeSearchGuildsWithInitialCallTask::FSubscribeSearchGuildsWithInitialCallTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Guild::Model::FGuildPtr>)> Callback,const FString GuildModelName,const FString UserId,const TOptional<FString> DisplayName,const TSharedPtr<TArray<int32>> Attributes1,const TSharedPtr<TArray<int32>> Attributes2,const TSharedPtr<TArray<int32>> Attributes3,const TSharedPtr<TArray<int32>> Attributes4,const TSharedPtr<TArray<int32>> Attributes5,const TSharedPtr<TArray<FString>> JoinPolicies,const TOptional<bool> IncludeFullMembersGuild,const TOptional<FString> OrderBy,const TOptional<FString> TimeOffsetToken) : Self(Self), Callback(Callback), QueryGuildModelName(GuildModelName), QueryUserId(UserId), QueryDisplayName(DisplayName), QueryAttributes1(Attributes1), QueryAttributes2(Attributes2), QueryAttributes3(Attributes3), QueryAttributes4(Attributes4), QueryAttributes5(Attributes5), QueryJoinPolicies(JoinPolicies), QueryIncludeFullMembersGuild(IncludeFullMembersGuild), QueryOrderBy(OrderBy), QueryTimeOffsetToken(TimeOffsetToken) {}
    FNamespaceDomain::FSubscribeSearchGuildsWithInitialCallTask::FSubscribeSearchGuildsWithInitialCallTask(const FSubscribeSearchGuildsWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryGuildModelName(From.QueryGuildModelName), QueryUserId(From.QueryUserId), QueryDisplayName(From.QueryDisplayName), QueryAttributes1(From.QueryAttributes1), QueryAttributes2(From.QueryAttributes2), QueryAttributes3(From.QueryAttributes3), QueryAttributes4(From.QueryAttributes4), QueryAttributes5(From.QueryAttributes5), QueryJoinPolicies(From.QueryJoinPolicies), QueryIncludeFullMembersGuild(From.QueryIncludeFullMembersGuild), QueryOrderBy(From.QueryOrderBy), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FSubscribeSearchGuildsWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectSearchGuildsTask>>(Self, TFunction<void(TArray<Gs2::Guild::Model::FGuildPtr>)>(), QueryGuildModelName, QueryUserId, QueryDisplayName, QueryAttributes1, QueryAttributes2, QueryAttributes3, QueryAttributes4, QueryAttributes5, QueryJoinPolicies, QueryIncludeFullMembersGuild, QueryOrderBy, QueryTimeOffsetToken);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeSearchGuilds(Callback, QueryGuildModelName, QueryUserId, QueryDisplayName, QueryAttributes1, QueryAttributes2, QueryAttributes3, QueryAttributes4, QueryAttributes5, QueryJoinPolicies, QueryIncludeFullMembersGuild, QueryOrderBy, QueryTimeOffsetToken);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FNamespaceDomain::FSubscribeSearchGuildsWithInitialCallTask>> FNamespaceDomain::SubscribeSearchGuildsWithInitialCall(TFunction<void(TArray<Gs2::Guild::Model::FGuildPtr>)> Callback,const FString GuildModelName,const FString UserId,const TOptional<FString> DisplayName,const TSharedPtr<TArray<int32>> Attributes1,const TSharedPtr<TArray<int32>> Attributes2,const TSharedPtr<TArray<int32>> Attributes3,const TSharedPtr<TArray<int32>> Attributes4,const TSharedPtr<TArray<int32>> Attributes5,const TSharedPtr<TArray<FString>> JoinPolicies,const TOptional<bool> IncludeFullMembersGuild,const TOptional<FString> OrderBy,const TOptional<FString> TimeOffsetToken)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeSearchGuildsWithInitialCallTask>>(this->AsShared(), Callback, GuildModelName, UserId, DisplayName, Attributes1, Attributes2, Attributes3, Attributes4, Attributes5, JoinPolicies, IncludeFullMembersGuild, OrderBy, TimeOffsetToken);
    }

    TSharedPtr<Gs2::Guild::Domain::Model::FUserDomain> FNamespaceDomain::User(
        const FString UserId
    )
    {
        return MakeShared<Gs2::Guild::Domain::Model::FUserDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId == TEXT("") ? TOptional<FString>() : TOptional<FString>(UserId)
        );
    }

    TSharedPtr<Gs2::Guild::Domain::Model::FUserAccessTokenDomain> FNamespaceDomain::AccessToken(
        Gs2::Auth::Model::FAccessTokenPtr AccessToken
    )
    {
        return MakeShared<Gs2::Guild::Domain::Model::FUserAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken
        );
    }

    TSharedPtr<Gs2::Guild::Domain::Model::FGuildDomain> FNamespaceDomain::Guild(
        const FString GuildModelName,
        const FString GuildName
    )
    {
        return MakeShared<Gs2::Guild::Domain::Model::FGuildDomain>(
            Gs2,
            Service,
            NamespaceName,
            GuildModelName == TEXT("") ? TOptional<FString>() : TOptional<FString>(GuildModelName),
            GuildName == TEXT("") ? TOptional<FString>() : TOptional<FString>(GuildName)
        );
    }

    TSharedPtr<Gs2::Guild::Domain::Model::FGuildAccessTokenDomain> FNamespaceDomain::GuildAccessToken(
        const FString GuildModelName,
        Gs2::Auth::Model::FAccessTokenPtr AccessToken,
        const TOptional<FString> GuildName
    )
    {
        return MakeShared<Gs2::Guild::Domain::Model::FGuildAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            GuildModelName == TEXT("") ? TOptional<FString>() : TOptional<FString>(GuildModelName),
            AccessToken,
            GuildName
        );
    }

    FString FNamespaceDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            ChildType;
    }

    FString FNamespaceDomain::CreateCacheKey(
        TOptional<FString> NamespaceName
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null");
    }

    FNamespaceDomain::FModelTask::FModelTask(
        const TSharedPtr<FNamespaceDomain> Self
    ): Self(Self)
    {

    }

    FNamespaceDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Guild::Model::FNamespace>> Result
    )
    {
        const auto ParentKey = FString("guild:Namespace");
        const FString CacheKey = Gs2::Guild::Domain::Model::FNamespaceDomain::CreateCacheKey(
            Self->NamespaceName
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Guild::Model::FNamespace::TypeName,
            ParentKey,
            CacheKey,
            [this, Result, CacheKey, ParentKey]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                // ReSharper disable once CppLocalVariableMayBeConst
                TSharedPtr<Gs2::Guild::Model::FNamespace> Value;
                auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Guild::Model::FNamespace>(
                    ParentKey,
                    CacheKey,
                    &Value
                );
                if (!bCacheHit) {
                    const auto Future = Self->Get(
                        MakeShared<Gs2::Guild::Request::FGetNamespaceRequest>()
                    );
                    Future->StartSynchronousTask();
                    if (Future->GetTask().IsError())
                    {
                        const auto Error = Future->GetTask().Error();
                        if (!Error.IsValid() || Error->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                        {
                            return Error;
                        }
                        Self->Gs2->Cache->Put(
                            Gs2::Guild::Model::FNamespace::TypeName,
                            ParentKey,
                            CacheKey,
                            nullptr,
                            FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                        );

                        if (!Error->GetErrors().IsValid() || Error->Count() == 0 || !Error->Detail(0).IsValid() || Error->Detail(0)->GetComponent() != "namespace")
                        {
                            return Error;
                        }
                    }
                    else
                    {
                        Value = Future->GetTask().Result();
                    }
                    Future->EnsureCompletion();
                }
                if (!bCacheHit)
                {
                    FGs2ObjectPtr ExistingObject;
                    const bool Existing = Self->Gs2->Cache->TryGet(
                        Gs2::Guild::Model::FNamespace::TypeName,
                        ParentKey,
                        CacheKey,
                        &ExistingObject
                    );
                    if (!Existing || ExistingObject != Value)
                    {
                        Self->Gs2->Cache->Put(
                            Gs2::Guild::Model::FNamespace::TypeName,
                            ParentKey,
                            CacheKey,
                            Value,
                            FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                        );
                    }
                }

                *Result = Value;

                return nullptr;
            }
        );
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FModelTask>> FNamespaceDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FNamespaceDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FNamespaceDomain::Subscribe(
        TFunction<void(Gs2::Guild::Model::FNamespacePtr)> Callback
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Guild::Domain::FGs2GuildDomain> WeakService = Service;
        const FString RegisteredParentKey = ParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;

        return Gs2->Cache->Subscribe(
            Gs2::Guild::Model::FNamespace::TypeName,
            ParentKey,
            Gs2::Guild::Domain::Model::FNamespaceDomain::CreateCacheKey(
                NamespaceName
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Guild::Model::FNamespace>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FNamespaceDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FNamespaceDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Guild::Model::FNamespace::TypeName,
            ParentKey,
            Gs2::Guild::Domain::Model::FNamespaceDomain::CreateCacheKey(
                NamespaceName
            ),
            CallbackID
        );
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

