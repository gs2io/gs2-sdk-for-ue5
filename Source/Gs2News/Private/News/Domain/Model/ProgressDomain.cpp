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

#include "News/Domain/Model/Progress.h"
#include "News/Domain/Model/Namespace.h"
#include "News/Domain/Model/Progress.h"
#include "News/Domain/Model/Output.h"
#include "News/Domain/Model/CurrentNewsMaster.h"
#include "News/Domain/Model/SetCookieRequestEntry.h"
#include "News/Domain/Model/NewsAccessToken.h"
#include "News/Domain/Model/User.h"
#include "News/Domain/Model/UserAccessToken.h"
#include "News/Domain/Model/News.h"
#include "News/Domain/Model/SetCookieRequestEntry.h"
#include "News/Model/Cache/Progress.h"
#include "News/Model/Cache/Output.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::News::Domain::Model
{

    FProgressDomain::FProgressDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const News::Domain::FGs2NewsDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UploadToken
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::News::FGs2NewsRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UploadToken(UploadToken),
        ParentKey(Gs2::News::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "Progress"
        ))
    {
    }

    FProgressDomain::FProgressDomain(
        const FProgressDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UploadToken(From.UploadToken),
        ParentKey(From.ParentKey)
    {

    }

    FProgressDomain::FGetTask::FGetTask(
        const TSharedPtr<FProgressDomain>& Self,
        const Request::FGetProgressRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FProgressDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FProgressDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::News::Model::FProgress>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUploadToken(Self->UploadToken);
        const auto Future = Self->Client->GetProgress(
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

        if (!ResultModel.IsValid() || !ResultModel->GetItem().IsValid())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("result.item"), TEXT("result.item is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }
        Gs2::News::Model::Cache::FProgressCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetUploadToken(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FProgressDomain::FGetTask>> FProgressDomain::Get(
        Request::FGetProgressRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    Gs2::News::Domain::Iterator::FDescribeOutputsIteratorPtr FProgressDomain::Outputs(
    ) const
    {
        return MakeShared<Gs2::News::Domain::Iterator::FDescribeOutputsIterator>(
            Gs2,
            Client,
            NamespaceName,
            UploadToken
        );
    }

    Gs2::Core::Domain::CallbackID FProgressDomain::SubscribeOutputs(
    TFunction<void()> Callback

    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::News::Model::FOutput::TypeName,
            Gs2::News::Model::Cache::FOutputCache::CreateCacheParentKey(
                NamespaceName,
                UploadToken,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FProgressDomain::UnsubscribeOutputs(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::News::Model::FOutput::TypeName,
            Gs2::News::Model::Cache::FOutputCache::CreateCacheParentKey(
                NamespaceName,
                UploadToken,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FProgressDomain::FCollectOutputsTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::News::Model::FOutputPtr>>, public TSharedFromThis<FCollectOutputsTask>
    {
        const TSharedPtr<FProgressDomain> Self;
        const TFunction<void(TArray<Gs2::News::Model::FOutputPtr>)> OnCollected;

    public:
        explicit FCollectOutputsTask(const TSharedPtr<FProgressDomain>& Self, TFunction<void(TArray<Gs2::News::Model::FOutputPtr>)> OnCollected) : Self(Self), OnCollected(OnCollected) {}
        FCollectOutputsTask(const FCollectOutputsTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::News::Model::FOutputPtr>>> Result) override
        {
            TArray<Gs2::News::Model::FOutputPtr> Items;
            auto Iterator = Self->Outputs()->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::News::Model::FOutputPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FProgressDomain::SubscribeOutputs(
        TFunction<void(TArray<Gs2::News::Model::FOutputPtr>)> Callback
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<News::Domain::FGs2NewsDomain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryUploadToken = UploadToken;
        const auto Parent = Gs2::News::Model::Cache::FOutputCache::CreateCacheParentKey(
        NamespaceName,
        UploadToken,
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::News::Model::FOutput::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::News::Model::FOutputPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::News::Model::FOutput>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryUploadToken]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FProgressDomain>(Owner, WeakService.Pin(), QueryNamespaceName, QueryUploadToken);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectOutputsTask>>(Domain, Callback);
                Task->StartBackgroundTask();
            }
        );
    }

    void FProgressDomain::InvalidateOutputs()
    {
        Gs2->Cache->ClearListCache(
            Gs2::News::Model::FOutput::TypeName,
            Gs2::News::Model::Cache::FOutputCache::CreateCacheParentKey(
        NamespaceName,
        UploadToken,
        TOptional<int32>()
    )
        );
    }

    FProgressDomain::FSubscribeOutputsWithInitialCallTask::FSubscribeOutputsWithInitialCallTask(const TSharedPtr<FProgressDomain>& Self, TFunction<void(TArray<Gs2::News::Model::FOutputPtr>)> Callback) : Self(Self), Callback(Callback) {}
    FProgressDomain::FSubscribeOutputsWithInitialCallTask::FSubscribeOutputsWithInitialCallTask(const FSubscribeOutputsWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback) {}
    Gs2::Core::Model::FGs2ErrorPtr FProgressDomain::FSubscribeOutputsWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectOutputsTask>>(Self, TFunction<void(TArray<Gs2::News::Model::FOutputPtr>)>());
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeOutputs(Callback);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FProgressDomain::FSubscribeOutputsWithInitialCallTask>> FProgressDomain::SubscribeOutputsWithInitialCall(TFunction<void(TArray<Gs2::News::Model::FOutputPtr>)> Callback)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeOutputsWithInitialCallTask>>(this->AsShared(), Callback);
    }

    TSharedPtr<Gs2::News::Domain::Model::FOutputDomain> FProgressDomain::Output(
        const FString OutputName
    )
    {
        return MakeShared<Gs2::News::Domain::Model::FOutputDomain>(
            Gs2,
            Service,
            NamespaceName,
            UploadToken,
            OutputName == TEXT("") ? TOptional<FString>() : TOptional<FString>(OutputName)
        );
    }

    FString FProgressDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UploadToken,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UploadToken.IsSet() ? *UploadToken : "null") + ":" +
            ChildType;
    }

    FString FProgressDomain::CreateCacheKey(
        TOptional<FString> UploadToken
    )
    {
        return FString("") +
            (UploadToken.IsSet() ? *UploadToken : "null");
    }

    FProgressDomain::FModelTask::FModelTask(
        const TSharedPtr<FProgressDomain> Self
    ): Self(Self)
    {

    }

    FProgressDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FProgressDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::News::Model::FProgress>> Result
    )
    {
        const auto CacheParentKey = Gs2::News::Model::Cache::FProgressCache::CreateCacheParentKey(

            Self->NamespaceName,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::News::Model::Cache::FProgressCache::CreateCacheKey(

            Self->UploadToken
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::News::Model::FProgress::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::News::Model::FProgressPtr Value;
                const auto CacheHit = Gs2::News::Model::Cache::FProgressCache::TryGet(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->UploadToken,
                    TOptional<int32>(),
                    &Value
                );
                if (CacheHit)
                {
                    *Result = Value;
                    return nullptr;
                }
                const auto Error = Gs2::News::Model::Cache::FProgressCache::Fetch(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->UploadToken,
                    TOptional<int32>(),
                    [Self](Gs2::News::Model::FProgressPtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::News::Request::FGetProgressRequest>()
                        );
                        Future->StartSynchronousTask();
                        if (Future->GetTask().IsError()) return Future->GetTask().Error();
                        *OutItem = Future->GetTask().Result();
                        Future->EnsureCompletion();
                        return nullptr;
                    },
                    &Value
                );
                if (Error.IsValid()) return Error;
                *Result = Value;
                return nullptr;
            }
        );
    }

    TSharedPtr<FAsyncTask<FProgressDomain::FModelTask>> FProgressDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FProgressDomain::FModelTask>>(this->AsShared());
    }

    void FProgressDomain::Invalidate()
    {
        Gs2::News::Model::Cache::FProgressCache::Delete(
            Gs2->Cache,

            NamespaceName,
            UploadToken,
            TOptional<int32>()
        );
    }

    FProgressDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FProgressDomain>& Self,
        TFunction<void(Gs2::News::Model::FProgressPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FProgressDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FProgressDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FProgressDomain::FSubscribeWithInitialCallTask>> FProgressDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::News::Model::FProgressPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FProgressDomain::Subscribe(
        TFunction<void(Gs2::News::Model::FProgressPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::News::Model::Cache::FProgressCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::News::Model::Cache::FProgressCache::CreateCacheKey(

            UploadToken
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<News::Domain::FGs2NewsDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryUploadToken = UploadToken;
        return Gs2->Cache->Subscribe(
            Gs2::News::Model::FProgress::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::News::Model::FProgress>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryUploadToken]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FProgressDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    QueryUploadToken
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FProgressDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::News::Model::Cache::FProgressCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::News::Model::Cache::FProgressCache::CreateCacheKey(

            UploadToken
        );
        Gs2->Cache->Unsubscribe(
            Gs2::News::Model::FProgress::TypeName,
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
