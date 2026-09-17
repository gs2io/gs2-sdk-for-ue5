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

#include "Account/Domain/Model/Namespace.h"
#include "Account/Domain/Model/Namespace.h"
#include "Account/Domain/Model/Account.h"
#include "Account/Domain/Model/AccountAccessToken.h"
#include "Account/Domain/Model/TakeOver.h"
#include "Account/Domain/Model/TakeOverAccessToken.h"
#include "Account/Domain/Model/PlatformId.h"
#include "Account/Domain/Model/PlatformIdAccessToken.h"
#include "Account/Domain/Model/DataOwner.h"
#include "Account/Domain/Model/DataOwnerAccessToken.h"
#include "Account/Domain/Model/TakeOverTypeModel.h"
#include "Account/Domain/Model/TakeOverTypeModelMaster.h"
#include "Account/Domain/Model/CurrentModelMaster.h"

#include "Account/Model/Cache/Account.h"
#include "Account/Model/Cache/TakeOverTypeModelMaster.h"
#include "Account/Model/Cache/TakeOverTypeModel.h"
#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Account::Domain::Model
{

    FNamespaceDomain::FNamespaceDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Account::Domain::FGs2AccountDomainPtr& Service,
        const TOptional<FString> NamespaceName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Account::FGs2AccountRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        ParentKey("account:Namespace")
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

    FNamespaceDomain::FGetAuthorizationUrlTask::FGetAuthorizationUrlTask(
        const TSharedPtr<FNamespaceDomain>& Self,
        const Request::FGetAuthorizationUrlRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FGetAuthorizationUrlTask::FGetAuthorizationUrlTask(
        const FGetAuthorizationUrlTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FGetAuthorizationUrlTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Account::Domain::Model::FNamespaceDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->GetAuthorizationUrl(
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
            if (ResultModel->GetAuthorizationUrl().IsSet())
            {
                Self->AuthorizationUrl = Domain->AuthorizationUrl = ResultModel->GetAuthorizationUrl();
            }
        }
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FGetAuthorizationUrlTask>> FNamespaceDomain::GetAuthorizationUrl(
        Request::FGetAuthorizationUrlRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetAuthorizationUrlTask>>(this->AsShared(), Request);
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
        TSharedPtr<TSharedPtr<Gs2::Account::Domain::Model::FNamespaceDomain>> Result
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
        TSharedPtr<TSharedPtr<Gs2::Account::Model::FNamespace>> Result
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
        TSharedPtr<TSharedPtr<Gs2::Account::Domain::Model::FNamespaceDomain>> Result
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
            const auto Key = Gs2::Account::Domain::Model::FNamespaceDomain::CreateCacheKey(
                ResultModel->GetItem()->GetName()
            );
            Self->Gs2->Cache->Put(
                Gs2::Account::Model::FNamespace::TypeName,
                Self->ParentKey,
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
        TSharedPtr<TSharedPtr<Gs2::Account::Domain::Model::FNamespaceDomain>> Result
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
        if (ResultModel->GetItem() != nullptr)
        {
            const auto Key = Gs2::Account::Domain::Model::FNamespaceDomain::CreateCacheKey(
                ResultModel->GetItem()->GetName()
            );
            Self->Gs2->Cache->Delete(
                Gs2::Account::Model::FNamespace::TypeName,
                Self->ParentKey,
                Key
            );
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FDeleteTask>> FNamespaceDomain::Delete(
        Request::FDeleteNamespaceRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FNamespaceDomain::FCreateAccountTask::FCreateAccountTask(
        const TSharedPtr<FNamespaceDomain>& Self,
        const Request::FCreateAccountRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FCreateAccountTask::FCreateAccountTask(
        const FCreateAccountTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FCreateAccountTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Account::Domain::Model::FAccountDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->CreateAccount(
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
            const auto ParentKey = Gs2::Account::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                Request->GetNamespaceName(),
                "Account"
            );
            const auto Key = Gs2::Account::Domain::Model::FAccountDomain::CreateCacheKey(
                ResultModel->GetItem()->GetUserId()
            );
            Self->Gs2->Cache->Put(
                Gs2::Account::Model::FAccount::TypeName,
                ParentKey,
                Key,
                ResultModel->GetItem(),
                FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
            );
        }
        auto Domain = MakeShared<Gs2::Account::Domain::Model::FAccountDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetUserId()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FCreateAccountTask>> FNamespaceDomain::CreateAccount(
        Request::FCreateAccountRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateAccountTask>>(this->AsShared(), Request);
    }

    FNamespaceDomain::FDoTakeOverTask::FDoTakeOverTask(
        const TSharedPtr<FNamespaceDomain>& Self,
        const Request::FDoTakeOverRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FDoTakeOverTask::FDoTakeOverTask(
        const FDoTakeOverTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FDoTakeOverTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Account::Domain::Model::FAccountDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->DoTakeOver(
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
            const auto Key = Gs2::Account::Domain::Model::FTakeOverDomain::CreateCacheKey(
                Request->GetType()
            );
            Self->Gs2->Cache->Put(
                Gs2::Account::Model::FTakeOver::TypeName,
                Self->ParentKey,
                Key,
                ResultModel->GetItem(),
                FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
            );
        }
        auto Domain = MakeShared<Gs2::Account::Domain::Model::FAccountDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetUserId()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FDoTakeOverTask>> FNamespaceDomain::DoTakeOver(
        Request::FDoTakeOverRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDoTakeOverTask>>(this->AsShared(), Request);
    }

    FNamespaceDomain::FDoTakeOverOpenIdConnectTask::FDoTakeOverOpenIdConnectTask(
        const TSharedPtr<FNamespaceDomain>& Self,
        const Request::FDoTakeOverOpenIdConnectRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FDoTakeOverOpenIdConnectTask::FDoTakeOverOpenIdConnectTask(
        const FDoTakeOverOpenIdConnectTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FDoTakeOverOpenIdConnectTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Account::Domain::Model::FAccountDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->DoTakeOverOpenIdConnect(
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
            const auto Key = Gs2::Account::Domain::Model::FTakeOverDomain::CreateCacheKey(
                Request->GetType()
            );
            Self->Gs2->Cache->Put(
                Gs2::Account::Model::FTakeOver::TypeName,
                Self->ParentKey,
                Key,
                ResultModel->GetItem(),
                FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
            );
        }
        auto Domain = MakeShared<Gs2::Account::Domain::Model::FAccountDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetUserId()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FDoTakeOverOpenIdConnectTask>> FNamespaceDomain::DoTakeOverOpenIdConnect(
        Request::FDoTakeOverOpenIdConnectRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDoTakeOverOpenIdConnectTask>>(this->AsShared(), Request);
    }

    FNamespaceDomain::FDeletePlatformIdByUserIdentifierTask::FDeletePlatformIdByUserIdentifierTask(
        const TSharedPtr<FNamespaceDomain>& Self,
        const Request::FDeletePlatformIdByUserIdentifierRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FDeletePlatformIdByUserIdentifierTask::FDeletePlatformIdByUserIdentifierTask(
        const FDeletePlatformIdByUserIdentifierTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FDeletePlatformIdByUserIdentifierTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Account::Domain::Model::FPlatformIdDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->DeletePlatformIdByUserIdentifier(
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
            const auto Key = Gs2::Account::Domain::Model::FPlatformIdDomain::CreateCacheKey(
                ResultModel->GetItem()->GetType()
            );
            Self->Gs2->Cache->Delete(
                Gs2::Account::Model::FPlatformId::TypeName,
                Self->ParentKey,
                Key
            );
        }
        auto Domain = MakeShared<Gs2::Account::Domain::Model::FPlatformIdDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetUserId(),
            ResultModel->GetItem()->GetType()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FDeletePlatformIdByUserIdentifierTask>> FNamespaceDomain::DeletePlatformIdByUserIdentifier(
        Request::FDeletePlatformIdByUserIdentifierRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeletePlatformIdByUserIdentifierTask>>(this->AsShared(), Request);
    }

    Gs2::Account::Domain::Iterator::FDescribeAccountsIteratorPtr FNamespaceDomain::Accounts(
    ) const
    {
        return MakeShared<Gs2::Account::Domain::Iterator::FDescribeAccountsIterator>(
            Gs2,
            Client,
            NamespaceName
        );
    }

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeAccounts(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Account::Model::FAccount::TypeName,
            Gs2::Account::Model::Cache::FAccountCache::CreateCacheParentKey(
                NamespaceName,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FNamespaceDomain::UnsubscribeAccounts(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Account::Model::FAccount::TypeName,
            Gs2::Account::Model::Cache::FAccountCache::CreateCacheParentKey(
                NamespaceName,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FNamespaceDomain::FCollectAccountsTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Account::Model::FAccountPtr>>, public TSharedFromThis<FCollectAccountsTask>
    {
        const TSharedPtr<FNamespaceDomain> Self;
        const TFunction<void(TArray<Gs2::Account::Model::FAccountPtr>)> OnCollected;

    public:
        explicit FCollectAccountsTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Account::Model::FAccountPtr>)> OnCollected) : Self(Self), OnCollected(OnCollected) {}
        FCollectAccountsTask(const FCollectAccountsTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Account::Model::FAccountPtr>>> Result) override
        {
            TArray<Gs2::Account::Model::FAccountPtr> Items;
            auto Iterator = Self->Accounts()->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Account::Model::FAccountPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeAccounts(
        TFunction<void(TArray<Gs2::Account::Model::FAccountPtr>)> Callback
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Account::Domain::FGs2AccountDomain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto Parent = Gs2::Account::Model::Cache::FAccountCache::CreateCacheParentKey(
        NamespaceName,
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Account::Model::FAccount::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Account::Model::FAccountPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Account::Model::FAccount>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FNamespaceDomain>(Owner, WeakService.Pin(), QueryNamespaceName);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectAccountsTask>>(Domain, Callback);
                Task->StartBackgroundTask();
            }
        );
    }

    void FNamespaceDomain::InvalidateAccounts()
    {
        Gs2->Cache->ClearListCache(
            Gs2::Account::Model::FAccount::TypeName,
            Gs2::Account::Model::Cache::FAccountCache::CreateCacheParentKey(
        NamespaceName,
        TOptional<int32>()
    )
        );
    }

    FNamespaceDomain::FSubscribeAccountsWithInitialCallTask::FSubscribeAccountsWithInitialCallTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Account::Model::FAccountPtr>)> Callback) : Self(Self), Callback(Callback) {}
    FNamespaceDomain::FSubscribeAccountsWithInitialCallTask::FSubscribeAccountsWithInitialCallTask(const FSubscribeAccountsWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback) {}
    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FSubscribeAccountsWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectAccountsTask>>(Self, TFunction<void(TArray<Gs2::Account::Model::FAccountPtr>)>());
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeAccounts(Callback);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FNamespaceDomain::FSubscribeAccountsWithInitialCallTask>> FNamespaceDomain::SubscribeAccountsWithInitialCall(TFunction<void(TArray<Gs2::Account::Model::FAccountPtr>)> Callback)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeAccountsWithInitialCallTask>>(this->AsShared(), Callback);
    }

    TSharedPtr<Gs2::Account::Domain::Model::FAccountDomain> FNamespaceDomain::Account(
        const FString UserId
    )
    {
        return MakeShared<Gs2::Account::Domain::Model::FAccountDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId == TEXT("") ? TOptional<FString>() : TOptional<FString>(UserId)
        );
    }

    TSharedPtr<Gs2::Account::Domain::Model::FAccountAccessTokenDomain> FNamespaceDomain::AccessToken(
        Gs2::Auth::Model::FAccessTokenPtr AccessToken
    )
    {
        return MakeShared<Gs2::Account::Domain::Model::FAccountAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken
        );
    }

    TSharedPtr<Gs2::Account::Domain::Model::FCurrentModelMasterDomain> FNamespaceDomain::CurrentModelMaster(
    )
    {
        return MakeShared<Gs2::Account::Domain::Model::FCurrentModelMasterDomain>(
            Gs2,
            Service,
            NamespaceName
        );
    }

    Gs2::Account::Domain::Iterator::FDescribeTakeOverTypeModelsIteratorPtr FNamespaceDomain::TakeOverTypeModels(
    ) const
    {
        return MakeShared<Gs2::Account::Domain::Iterator::FDescribeTakeOverTypeModelsIterator>(
            Gs2,
            Client,
            NamespaceName
        );
    }

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeTakeOverTypeModels(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Account::Model::FTakeOverTypeModel::TypeName,
            Gs2::Account::Model::Cache::FTakeOverTypeModelCache::CreateCacheParentKey(
                NamespaceName,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FNamespaceDomain::UnsubscribeTakeOverTypeModels(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Account::Model::FTakeOverTypeModel::TypeName,
            Gs2::Account::Model::Cache::FTakeOverTypeModelCache::CreateCacheParentKey(
                NamespaceName,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FNamespaceDomain::FCollectTakeOverTypeModelsTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Account::Model::FTakeOverTypeModelPtr>>, public TSharedFromThis<FCollectTakeOverTypeModelsTask>
    {
        const TSharedPtr<FNamespaceDomain> Self;
        const TFunction<void(TArray<Gs2::Account::Model::FTakeOverTypeModelPtr>)> OnCollected;

    public:
        explicit FCollectTakeOverTypeModelsTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Account::Model::FTakeOverTypeModelPtr>)> OnCollected) : Self(Self), OnCollected(OnCollected) {}
        FCollectTakeOverTypeModelsTask(const FCollectTakeOverTypeModelsTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Account::Model::FTakeOverTypeModelPtr>>> Result) override
        {
            TArray<Gs2::Account::Model::FTakeOverTypeModelPtr> Items;
            auto Iterator = Self->TakeOverTypeModels()->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Account::Model::FTakeOverTypeModelPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeTakeOverTypeModels(
        TFunction<void(TArray<Gs2::Account::Model::FTakeOverTypeModelPtr>)> Callback
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Account::Domain::FGs2AccountDomain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto Parent = Gs2::Account::Model::Cache::FTakeOverTypeModelCache::CreateCacheParentKey(
        NamespaceName,
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Account::Model::FTakeOverTypeModel::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Account::Model::FTakeOverTypeModelPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Account::Model::FTakeOverTypeModel>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FNamespaceDomain>(Owner, WeakService.Pin(), QueryNamespaceName);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectTakeOverTypeModelsTask>>(Domain, Callback);
                Task->StartBackgroundTask();
            }
        );
    }

    void FNamespaceDomain::InvalidateTakeOverTypeModels()
    {
        Gs2->Cache->ClearListCache(
            Gs2::Account::Model::FTakeOverTypeModel::TypeName,
            Gs2::Account::Model::Cache::FTakeOverTypeModelCache::CreateCacheParentKey(
        NamespaceName,
        TOptional<int32>()
    )
        );
    }

    FNamespaceDomain::FSubscribeTakeOverTypeModelsWithInitialCallTask::FSubscribeTakeOverTypeModelsWithInitialCallTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Account::Model::FTakeOverTypeModelPtr>)> Callback) : Self(Self), Callback(Callback) {}
    FNamespaceDomain::FSubscribeTakeOverTypeModelsWithInitialCallTask::FSubscribeTakeOverTypeModelsWithInitialCallTask(const FSubscribeTakeOverTypeModelsWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback) {}
    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FSubscribeTakeOverTypeModelsWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectTakeOverTypeModelsTask>>(Self, TFunction<void(TArray<Gs2::Account::Model::FTakeOverTypeModelPtr>)>());
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeTakeOverTypeModels(Callback);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FNamespaceDomain::FSubscribeTakeOverTypeModelsWithInitialCallTask>> FNamespaceDomain::SubscribeTakeOverTypeModelsWithInitialCall(TFunction<void(TArray<Gs2::Account::Model::FTakeOverTypeModelPtr>)> Callback)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeTakeOverTypeModelsWithInitialCallTask>>(this->AsShared(), Callback);
    }

    TSharedPtr<Gs2::Account::Domain::Model::FTakeOverTypeModelDomain> FNamespaceDomain::TakeOverTypeModel(
        const int32 Type
    )
    {
        return MakeShared<Gs2::Account::Domain::Model::FTakeOverTypeModelDomain>(
            Gs2,
            Service,
            NamespaceName,
            Type
        );
    }

    Gs2::Account::Domain::Iterator::FDescribeTakeOverTypeModelMastersIteratorPtr FNamespaceDomain::TakeOverTypeModelMasters(
    ) const
    {
        return MakeShared<Gs2::Account::Domain::Iterator::FDescribeTakeOverTypeModelMastersIterator>(
            Gs2,
            Client,
            NamespaceName
        );
    }

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeTakeOverTypeModelMasters(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Account::Model::FTakeOverTypeModelMaster::TypeName,
            Gs2::Account::Model::Cache::FTakeOverTypeModelMasterCache::CreateCacheParentKey(
                NamespaceName,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FNamespaceDomain::UnsubscribeTakeOverTypeModelMasters(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Account::Model::FTakeOverTypeModelMaster::TypeName,
            Gs2::Account::Model::Cache::FTakeOverTypeModelMasterCache::CreateCacheParentKey(
                NamespaceName,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FNamespaceDomain::FCollectTakeOverTypeModelMastersTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Account::Model::FTakeOverTypeModelMasterPtr>>, public TSharedFromThis<FCollectTakeOverTypeModelMastersTask>
    {
        const TSharedPtr<FNamespaceDomain> Self;
        const TFunction<void(TArray<Gs2::Account::Model::FTakeOverTypeModelMasterPtr>)> OnCollected;

    public:
        explicit FCollectTakeOverTypeModelMastersTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Account::Model::FTakeOverTypeModelMasterPtr>)> OnCollected) : Self(Self), OnCollected(OnCollected) {}
        FCollectTakeOverTypeModelMastersTask(const FCollectTakeOverTypeModelMastersTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Account::Model::FTakeOverTypeModelMasterPtr>>> Result) override
        {
            TArray<Gs2::Account::Model::FTakeOverTypeModelMasterPtr> Items;
            auto Iterator = Self->TakeOverTypeModelMasters()->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Account::Model::FTakeOverTypeModelMasterPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeTakeOverTypeModelMasters(
        TFunction<void(TArray<Gs2::Account::Model::FTakeOverTypeModelMasterPtr>)> Callback
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Account::Domain::FGs2AccountDomain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto Parent = Gs2::Account::Model::Cache::FTakeOverTypeModelMasterCache::CreateCacheParentKey(
        NamespaceName,
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Account::Model::FTakeOverTypeModelMaster::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Account::Model::FTakeOverTypeModelMasterPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Account::Model::FTakeOverTypeModelMaster>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FNamespaceDomain>(Owner, WeakService.Pin(), QueryNamespaceName);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectTakeOverTypeModelMastersTask>>(Domain, Callback);
                Task->StartBackgroundTask();
            }
        );
    }

    void FNamespaceDomain::InvalidateTakeOverTypeModelMasters()
    {
        Gs2->Cache->ClearListCache(
            Gs2::Account::Model::FTakeOverTypeModelMaster::TypeName,
            Gs2::Account::Model::Cache::FTakeOverTypeModelMasterCache::CreateCacheParentKey(
        NamespaceName,
        TOptional<int32>()
    )
        );
    }

    FNamespaceDomain::FSubscribeTakeOverTypeModelMastersWithInitialCallTask::FSubscribeTakeOverTypeModelMastersWithInitialCallTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Account::Model::FTakeOverTypeModelMasterPtr>)> Callback) : Self(Self), Callback(Callback) {}
    FNamespaceDomain::FSubscribeTakeOverTypeModelMastersWithInitialCallTask::FSubscribeTakeOverTypeModelMastersWithInitialCallTask(const FSubscribeTakeOverTypeModelMastersWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback) {}
    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FSubscribeTakeOverTypeModelMastersWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectTakeOverTypeModelMastersTask>>(Self, TFunction<void(TArray<Gs2::Account::Model::FTakeOverTypeModelMasterPtr>)>());
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeTakeOverTypeModelMasters(Callback);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FNamespaceDomain::FSubscribeTakeOverTypeModelMastersWithInitialCallTask>> FNamespaceDomain::SubscribeTakeOverTypeModelMastersWithInitialCall(TFunction<void(TArray<Gs2::Account::Model::FTakeOverTypeModelMasterPtr>)> Callback)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeTakeOverTypeModelMastersWithInitialCallTask>>(this->AsShared(), Callback);
    }

    TSharedPtr<Gs2::Account::Domain::Model::FTakeOverTypeModelMasterDomain> FNamespaceDomain::TakeOverTypeModelMaster(
        const int32 Type
    )
    {
        return MakeShared<Gs2::Account::Domain::Model::FTakeOverTypeModelMasterDomain>(
            Gs2,
            Service,
            NamespaceName,
            Type
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
        TSharedPtr<TSharedPtr<Gs2::Account::Model::FNamespace>> Result
    )
    {
        const auto ParentKey = FString("account:Namespace");
        const FString CacheKey = Gs2::Account::Domain::Model::FNamespaceDomain::CreateCacheKey(
            Self->NamespaceName
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Account::Model::FNamespace::TypeName,
            ParentKey,
            CacheKey,
            [this, Result, CacheKey, ParentKey]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                // ReSharper disable once CppLocalVariableMayBeConst
                TSharedPtr<Gs2::Account::Model::FNamespace> Value;
                auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Account::Model::FNamespace>(
                    ParentKey,
                    CacheKey,
                    &Value
                );
                if (!bCacheHit) {
                    const auto Future = Self->Get(
                        MakeShared<Gs2::Account::Request::FGetNamespaceRequest>()
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
                            Gs2::Account::Model::FNamespace::TypeName,
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
                        Gs2::Account::Model::FNamespace::TypeName,
                        ParentKey,
                        CacheKey,
                        &ExistingObject
                    );
                    if (!Existing || ExistingObject != Value)
                    {
                        Self->Gs2->Cache->Put(
                            Gs2::Account::Model::FNamespace::TypeName,
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
        TFunction<void(Gs2::Account::Model::FNamespacePtr)> Callback
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Account::Domain::FGs2AccountDomain> WeakService = Service;
        const FString RegisteredParentKey = ParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;

        return Gs2->Cache->Subscribe(
            Gs2::Account::Model::FNamespace::TypeName,
            ParentKey,
            Gs2::Account::Domain::Model::FNamespaceDomain::CreateCacheKey(
                NamespaceName
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Account::Model::FNamespace>(obj));
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
            Gs2::Account::Model::FNamespace::TypeName,
            ParentKey,
            Gs2::Account::Domain::Model::FNamespaceDomain::CreateCacheKey(
                NamespaceName
            ),
            CallbackID
        );
    }
    
    FNamespaceDomain::FDeleteTakeOverByUserIdentifierTask::FDeleteTakeOverByUserIdentifierTask(
        const TSharedPtr<FNamespaceDomain>& Self,
        const Request::FDeleteTakeOverByUserIdentifierRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FDeleteTakeOverByUserIdentifierTask::FDeleteTakeOverByUserIdentifierTask(
        const FDeleteTakeOverByUserIdentifierTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FDeleteTakeOverByUserIdentifierTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Account::Domain::Model::FTakeOverDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->DeleteTakeOverByUserIdentifier(
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
        auto Domain = MakeShared<Gs2::Account::Domain::Model::FTakeOverDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetUserId(),
            ResultModel->GetItem()->GetType()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FDeleteTakeOverByUserIdentifierTask>> FNamespaceDomain::DeleteTakeOverByUserIdentifier(
        Request::FDeleteTakeOverByUserIdentifierRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTakeOverByUserIdentifierTask>>(this->AsShared(), Request);
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

