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

#include "Deploy/Domain/Gs2Deploy.h"
#include "Deploy/Domain/Model/Stack.h"
#include "Deploy/Domain/Model/Resource.h"
#include "Deploy/Domain/Model/Event.h"
#include "Deploy/Domain/Model/Output.h"

#include "Deploy/Model/Cache/Stack.h"
#include "Deploy/Model/Cache/Resource.h"
#include "Deploy/Model/Cache/Event.h"
#include "Deploy/Model/Cache/Output.h"

#include "Core/Domain/Gs2.h"

namespace Gs2::Deploy::Domain
{

    FGs2DeployDomain::FGs2DeployDomain(
        const Core::Domain::FGs2Ptr& Gs2
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Client(MakeShared<Gs2::Deploy::FGs2DeployRestClient>(Gs2->RestSession)),
        ParentKey("deploy")
    {
    }

    FGs2DeployDomain::FGs2DeployDomain(
        const FGs2DeployDomain& From
    ):
        Gs2(From.Gs2),
        Client(From.Client),
        ParentKey(From.ParentKey)
    {

    }

    FGs2DeployDomain::FPreCreateStackTask::FPreCreateStackTask(
        const TSharedPtr<FGs2DeployDomain>& Self,
        const Request::FPreCreateStackRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2DeployDomain::FPreCreateStackTask::FPreCreateStackTask(
        const FPreCreateStackTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2DeployDomain::FPreCreateStackTask::Action(
        TSharedPtr<TSharedPtr<FGs2DeployDomain>> Result
    )
    {
        const auto Future = Self->Client->PreCreateStack(
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

    TSharedPtr<FAsyncTask<FGs2DeployDomain::FPreCreateStackTask>> FGs2DeployDomain::PreCreateStack(
        Request::FPreCreateStackRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FPreCreateStackTask>>(this->AsShared(), Request);
    }

    FGs2DeployDomain::FCreateStackTask::FCreateStackTask(
        const TSharedPtr<FGs2DeployDomain>& Self,
        const Request::FCreateStackRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2DeployDomain::FCreateStackTask::FCreateStackTask(
        const FCreateStackTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2DeployDomain::FCreateStackTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Deploy::Domain::Model::FStackDomain>> Result
    )
    {
        const auto Future = Self->Client->CreateStack(
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


        Gs2::Deploy::Model::Cache::FStackCache::Put(
            Self->Gs2->Cache,

            ResultModel->GetItem()->GetName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        auto Domain = MakeShared<Gs2::Deploy::Domain::Model::FStackDomain>(
            Self->Gs2,
            Self,
            ResultModel->GetItem()->GetName()
        );
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGs2DeployDomain::FCreateStackTask>> FGs2DeployDomain::CreateStack(
        Request::FCreateStackRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateStackTask>>(this->AsShared(), Request);
    }

    FGs2DeployDomain::FCreateStackFromGitHubTask::FCreateStackFromGitHubTask(
        const TSharedPtr<FGs2DeployDomain>& Self,
        const Request::FCreateStackFromGitHubRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2DeployDomain::FCreateStackFromGitHubTask::FCreateStackFromGitHubTask(
        const FCreateStackFromGitHubTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2DeployDomain::FCreateStackFromGitHubTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Deploy::Domain::Model::FStackDomain>> Result
    )
    {
        const auto Future = Self->Client->CreateStackFromGitHub(
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


        Gs2::Deploy::Model::Cache::FStackCache::Put(
            Self->Gs2->Cache,

            ResultModel->GetItem()->GetName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        auto Domain = MakeShared<Gs2::Deploy::Domain::Model::FStackDomain>(
            Self->Gs2,
            Self,
            ResultModel->GetItem()->GetName()
        );
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGs2DeployDomain::FCreateStackFromGitHubTask>> FGs2DeployDomain::CreateStackFromGitHub(
        Request::FCreateStackFromGitHubRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateStackFromGitHubTask>>(this->AsShared(), Request);
    }

    FGs2DeployDomain::FPreValidateTask::FPreValidateTask(
        const TSharedPtr<FGs2DeployDomain>& Self,
        const Request::FPreValidateRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2DeployDomain::FPreValidateTask::FPreValidateTask(
        const FPreValidateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2DeployDomain::FPreValidateTask::Action(
        TSharedPtr<TSharedPtr<FGs2DeployDomain>> Result
    )
    {
        const auto Future = Self->Client->PreValidate(
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

    TSharedPtr<FAsyncTask<FGs2DeployDomain::FPreValidateTask>> FGs2DeployDomain::PreValidate(
        Request::FPreValidateRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FPreValidateTask>>(this->AsShared(), Request);
    }

    FGs2DeployDomain::FValidateTask::FValidateTask(
        const TSharedPtr<FGs2DeployDomain>& Self,
        const Request::FValidateRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2DeployDomain::FValidateTask::FValidateTask(
        const FValidateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2DeployDomain::FValidateTask::Action(
        TSharedPtr<TSharedPtr<FGs2DeployDomain>> Result
    )
    {
        const auto Future = Self->Client->Validate(
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

    TSharedPtr<FAsyncTask<FGs2DeployDomain::FValidateTask>> FGs2DeployDomain::Validate(
        Request::FValidateRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FValidateTask>>(this->AsShared(), Request);
    }

    Gs2::Deploy::Domain::Iterator::FDescribeStacksIteratorPtr FGs2DeployDomain::Stacks(
        const TOptional<FString> NamePrefix
    ) const
    {
        return MakeShared<Gs2::Deploy::Domain::Iterator::FDescribeStacksIterator>(
            Gs2,
            Client,
            NamePrefix
        );
    }

    Gs2::Core::Domain::CallbackID FGs2DeployDomain::SubscribeStacks(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Deploy::Model::FStack::TypeName,
            Gs2::Deploy::Model::Cache::FStackCache::CreateCacheParentKey(
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FGs2DeployDomain::UnsubscribeStacks(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Deploy::Model::FStack::TypeName,
            Gs2::Deploy::Model::Cache::FStackCache::CreateCacheParentKey(
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FGs2DeployDomain::FCollectStacksTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Deploy::Model::FStackPtr>>, public TSharedFromThis<FCollectStacksTask>
    {
        const TSharedPtr<FGs2DeployDomain> Self;
        const TFunction<void(TArray<Gs2::Deploy::Model::FStackPtr>)> OnCollected;
    const TOptional<FString> QueryNamePrefix;
    public:
        explicit FCollectStacksTask(const TSharedPtr<FGs2DeployDomain>& Self, TFunction<void(TArray<Gs2::Deploy::Model::FStackPtr>)> OnCollected,const TOptional<FString> NamePrefix) : Self(Self), OnCollected(OnCollected), QueryNamePrefix(NamePrefix) {}
        FCollectStacksTask(const FCollectStacksTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryNamePrefix(From.QueryNamePrefix) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Deploy::Model::FStackPtr>>> Result) override
        {
            TArray<Gs2::Deploy::Model::FStackPtr> Items;
            auto Iterator = Self->Stacks(QueryNamePrefix)->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Deploy::Model::FStackPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FGs2DeployDomain::SubscribeStacks(
        TFunction<void(TArray<Gs2::Deploy::Model::FStackPtr>)> Callback,const TOptional<FString> NamePrefix
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const auto QueryNamePrefix = NamePrefix;
        const auto Parent = Gs2::Deploy::Model::Cache::FStackCache::CreateCacheParentKey(
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Deploy::Model::FStack::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Deploy::Model::FStackPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Deploy::Model::FStack>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, Callback, QueryNamePrefix]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FGs2DeployDomain>(Owner);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectStacksTask>>(Domain, Callback, QueryNamePrefix);
                Task->StartBackgroundTask();
            }
        );
    }

    void FGs2DeployDomain::InvalidateStacks(const TOptional<FString> NamePrefix)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Deploy::Model::FStack::TypeName,
            Gs2::Deploy::Model::Cache::FStackCache::CreateCacheParentKey(
        TOptional<int32>()
    )
        );
    }

    FGs2DeployDomain::FSubscribeStacksWithInitialCallTask::FSubscribeStacksWithInitialCallTask(const TSharedPtr<FGs2DeployDomain>& Self, TFunction<void(TArray<Gs2::Deploy::Model::FStackPtr>)> Callback,const TOptional<FString> NamePrefix) : Self(Self), Callback(Callback), QueryNamePrefix(NamePrefix) {}
    FGs2DeployDomain::FSubscribeStacksWithInitialCallTask::FSubscribeStacksWithInitialCallTask(const FSubscribeStacksWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryNamePrefix(From.QueryNamePrefix) {}
    Gs2::Core::Model::FGs2ErrorPtr FGs2DeployDomain::FSubscribeStacksWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectStacksTask>>(Self, TFunction<void(TArray<Gs2::Deploy::Model::FStackPtr>)>(), QueryNamePrefix);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeStacks(Callback, QueryNamePrefix);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FGs2DeployDomain::FSubscribeStacksWithInitialCallTask>> FGs2DeployDomain::SubscribeStacksWithInitialCall(TFunction<void(TArray<Gs2::Deploy::Model::FStackPtr>)> Callback,const TOptional<FString> NamePrefix)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeStacksWithInitialCallTask>>(this->AsShared(), Callback, NamePrefix);
    }

    TSharedPtr<Gs2::Deploy::Domain::Model::FStackDomain> FGs2DeployDomain::Stack(
        const FString StackName
    )
    {
        return MakeShared<Gs2::Deploy::Domain::Model::FStackDomain>(
            Gs2,
            AsShared(),
            StackName == TEXT("") ? TOptional<FString>() : TOptional<FString>(StackName)
        );
    }

    void FGs2DeployDomain::UpdateCacheFromStampSheet(
        const FString Method,
        const FString Request,
        const FString Result,
        const TOptional<int32> TimeOffset
    ) {
    }

    TOptional<FString> FGs2DeployDomain::PutUserData(
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<int32> TimeOffset,
        const FString Kind,
        const FString Payload
    ) {
        return TOptional<FString>();
    }

    bool FGs2DeployDomain::SetListCached(
        const TOptional<int32> TimeOffset,
        const FString Kind,
        const FString ParentKey
    ) {
        return false;
    }

    void FGs2DeployDomain::UpdateCacheFromStampTask(
        const FString Method,
        const FString Request,
        const FString Result,
        const TOptional<int32> TimeOffset
    ) {
    }

    void FGs2DeployDomain::UpdateCacheFromJobResult(
        const FString Method,
        const Gs2::JobQueue::Model::FJobPtr Job,
        const Gs2::JobQueue::Model::FJobResultBodyPtr Result,
        const TOptional<int32> TimeOffset
    ) {
    }

    void FGs2DeployDomain::HandleNotification(
        const FString Action,
        const FString Payload
    ) {
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif
