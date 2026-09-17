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

#include "SerialKey/Domain/Model/User.h"
#include "SerialKey/Domain/Model/Namespace.h"
#include "SerialKey/Domain/Model/IssueJob.h"
#include "SerialKey/Domain/Model/SerialKey.h"
#include "SerialKey/Domain/Model/SerialKeyAccessToken.h"
#include "SerialKey/Domain/Model/User.h"
#include "SerialKey/Domain/Model/UserAccessToken.h"
#include "SerialKey/Domain/Model/CampaignModel.h"
#include "SerialKey/Domain/Model/CampaignModelMaster.h"
#include "SerialKey/Domain/Model/CurrentCampaignMaster.h"
#include "SerialKey/Model/Cache/SerialKey.h"
#include "SerialKey/Model/Cache/CampaignModel.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::SerialKey::Domain::Model
{

    FUserDomain::FUserDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const SerialKey::Domain::FGs2SerialKeyDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::SerialKey::FGs2SerialKeyRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        ParentKey(Gs2::SerialKey::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "User"
        ))
    {
    }

    FUserDomain::FUserDomain(
        const FUserDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        ParentKey(From.ParentKey)
    {

    }

    FUserDomain::FDownloadSerialCodesTask::FDownloadSerialCodesTask(
        const TSharedPtr<FUserDomain>& Self,
        const Request::FDownloadSerialCodesRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserDomain::FDownloadSerialCodesTask::FDownloadSerialCodesTask(
        const FDownloadSerialCodesTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FDownloadSerialCodesTask::Action(
        TSharedPtr<TSharedPtr<Gs2::SerialKey::Domain::Model::FUserDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->DownloadSerialCodes(
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

    TSharedPtr<FAsyncTask<FUserDomain::FDownloadSerialCodesTask>> FUserDomain::DownloadSerialCodes(
        Request::FDownloadSerialCodesRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDownloadSerialCodesTask>>(this->AsShared(), Request);
    }

    FUserDomain::FIssueOnceTask::FIssueOnceTask(
        const TSharedPtr<FUserDomain>& Self,
        const Request::FIssueOnceRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserDomain::FIssueOnceTask::FIssueOnceTask(
        const FIssueOnceTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FIssueOnceTask::Action(
        TSharedPtr<TSharedPtr<Gs2::SerialKey::Domain::Model::FSerialKeyDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->IssueOnce(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();

        auto Domain = MakeShared<Gs2::SerialKey::Domain::Model::FSerialKeyDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            Self->UserId,
            ResultModel->GetItem()->GetCode()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserDomain::FIssueOnceTask>> FUserDomain::IssueOnce(
        Request::FIssueOnceRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FIssueOnceTask>>(this->AsShared(), Request);
    }

    FUserDomain::FVerifyCodeTask::FVerifyCodeTask(
        const TSharedPtr<FUserDomain>& Self,
        const Request::FVerifyCodeByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserDomain::FVerifyCodeTask::FVerifyCodeTask(
        const FVerifyCodeTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FVerifyCodeTask::Action(
        TSharedPtr<TSharedPtr<Gs2::SerialKey::Domain::Model::FSerialKeyDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->VerifyCodeByUserId(
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

        if (!(Request->GetUserId()).IsSet())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("userId"), TEXT("userId is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }
        Gs2::SerialKey::Model::Cache::FSerialKeyCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetUserId(),
            ResultModel->GetItem()->GetCode(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
            if (ResultModel.IsValid() && ResultModel->GetCampaignModel() != nullptr)
            {

        if (!ResultModel.IsValid() || !ResultModel->GetItem().IsValid())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("result.item"), TEXT("result.item is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }
        Gs2::SerialKey::Model::Cache::FCampaignModelCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetCampaignModelName(),
            TOptional<int32>(),
            ResultModel->GetCampaignModel()
        );
            }
        auto Domain = MakeShared<Gs2::SerialKey::Domain::Model::FSerialKeyDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            Request->GetUserId(),
            ResultModel->GetItem()->GetCode()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserDomain::FVerifyCodeTask>> FUserDomain::VerifyCode(
        Request::FVerifyCodeByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FVerifyCodeTask>>(this->AsShared(), Request);
    }

    FUserDomain::FRevertUseTask::FRevertUseTask(
        const TSharedPtr<FUserDomain>& Self,
        const Request::FRevertUseByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserDomain::FRevertUseTask::FRevertUseTask(
        const FRevertUseTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FRevertUseTask::Action(
        TSharedPtr<TSharedPtr<Gs2::SerialKey::Domain::Model::FSerialKeyDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->RevertUseByUserId(
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

        if (!(Request->GetUserId()).IsSet())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("userId"), TEXT("userId is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }
        Gs2::SerialKey::Model::Cache::FSerialKeyCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetUserId(),
            ResultModel->GetItem()->GetCode(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
            if (ResultModel.IsValid() && ResultModel->GetCampaignModel() != nullptr)
            {

        if (!ResultModel.IsValid() || !ResultModel->GetItem().IsValid())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("result.item"), TEXT("result.item is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }
        Gs2::SerialKey::Model::Cache::FCampaignModelCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetCampaignModelName(),
            TOptional<int32>(),
            ResultModel->GetCampaignModel()
        );
            }
        auto Domain = MakeShared<Gs2::SerialKey::Domain::Model::FSerialKeyDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            Request->GetUserId(),
            ResultModel->GetItem()->GetCode()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserDomain::FRevertUseTask>> FUserDomain::RevertUse(
        Request::FRevertUseByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FRevertUseTask>>(this->AsShared(), Request);
    }

    Gs2::SerialKey::Domain::Iterator::FDescribeSerialKeysIteratorPtr FUserDomain::SerialKeys(
        const FString CampaignModelName,
        const TOptional<FString> IssueJobName
    ) const
    {
        return MakeShared<Gs2::SerialKey::Domain::Iterator::FDescribeSerialKeysIterator>(
            Gs2,
            Client,
            NamespaceName,
            CampaignModelName,
            IssueJobName
        );
    }

    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeSerialKeys(
    TFunction<void()> Callback

    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::SerialKey::Model::FSerialKey::TypeName,
            Gs2::SerialKey::Model::Cache::FSerialKeyCache::CreateCacheParentKey(
                NamespaceName,
                TOptional<FString>(),
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FUserDomain::UnsubscribeSerialKeys(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::SerialKey::Model::FSerialKey::TypeName,
            Gs2::SerialKey::Model::Cache::FSerialKeyCache::CreateCacheParentKey(
                NamespaceName,
                TOptional<FString>(),
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FUserDomain::FCollectSerialKeysTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::SerialKey::Model::FSerialKeyPtr>>, public TSharedFromThis<FCollectSerialKeysTask>
    {
        const TSharedPtr<FUserDomain> Self;
        const TFunction<void(TArray<Gs2::SerialKey::Model::FSerialKeyPtr>)> OnCollected;
    const FString QueryCampaignModelName;const TOptional<FString> QueryIssueJobName;
    public:
        explicit FCollectSerialKeysTask(const TSharedPtr<FUserDomain>& Self, TFunction<void(TArray<Gs2::SerialKey::Model::FSerialKeyPtr>)> OnCollected,const FString CampaignModelName,const TOptional<FString> IssueJobName) : Self(Self), OnCollected(OnCollected), QueryCampaignModelName(CampaignModelName), QueryIssueJobName(IssueJobName) {}
        FCollectSerialKeysTask(const FCollectSerialKeysTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryCampaignModelName(From.QueryCampaignModelName), QueryIssueJobName(From.QueryIssueJobName) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::SerialKey::Model::FSerialKeyPtr>>> Result) override
        {
            TArray<Gs2::SerialKey::Model::FSerialKeyPtr> Items;
            auto Iterator = Self->SerialKeys(QueryCampaignModelName, QueryIssueJobName)->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::SerialKey::Model::FSerialKeyPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeSerialKeys(
        TFunction<void(TArray<Gs2::SerialKey::Model::FSerialKeyPtr>)> Callback,const FString CampaignModelName,const TOptional<FString> IssueJobName
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<SerialKey::Domain::FGs2SerialKeyDomain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryUserId = UserId;
        const auto QueryCampaignModelName = CampaignModelName;
        const auto QueryIssueJobName = IssueJobName;
        const auto Parent = Gs2::SerialKey::Model::Cache::FSerialKeyCache::CreateCacheParentKey(
        NamespaceName,
        TOptional<FString>(),
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::SerialKey::Model::FSerialKey::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::SerialKey::Model::FSerialKeyPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::SerialKey::Model::FSerialKey>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryUserId, QueryCampaignModelName, QueryIssueJobName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FUserDomain>(Owner, WeakService.Pin(), QueryNamespaceName, QueryUserId);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectSerialKeysTask>>(Domain, Callback, QueryCampaignModelName, QueryIssueJobName);
                Task->StartBackgroundTask();
            }
        );
    }

    void FUserDomain::InvalidateSerialKeys(const FString CampaignModelName,const TOptional<FString> IssueJobName)
    {
        Gs2->Cache->ClearListCache(
            Gs2::SerialKey::Model::FSerialKey::TypeName,
            Gs2::SerialKey::Model::Cache::FSerialKeyCache::CreateCacheParentKey(
        NamespaceName,
        TOptional<FString>(),
        TOptional<int32>()
    )
        );
    }

    FUserDomain::FSubscribeSerialKeysWithInitialCallTask::FSubscribeSerialKeysWithInitialCallTask(const TSharedPtr<FUserDomain>& Self, TFunction<void(TArray<Gs2::SerialKey::Model::FSerialKeyPtr>)> Callback,const FString CampaignModelName,const TOptional<FString> IssueJobName) : Self(Self), Callback(Callback), QueryCampaignModelName(CampaignModelName), QueryIssueJobName(IssueJobName) {}
    FUserDomain::FSubscribeSerialKeysWithInitialCallTask::FSubscribeSerialKeysWithInitialCallTask(const FSubscribeSerialKeysWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryCampaignModelName(From.QueryCampaignModelName), QueryIssueJobName(From.QueryIssueJobName) {}
    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FSubscribeSerialKeysWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectSerialKeysTask>>(Self, TFunction<void(TArray<Gs2::SerialKey::Model::FSerialKeyPtr>)>(), QueryCampaignModelName, QueryIssueJobName);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeSerialKeys(Callback, QueryCampaignModelName, QueryIssueJobName);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FUserDomain::FSubscribeSerialKeysWithInitialCallTask>> FUserDomain::SubscribeSerialKeysWithInitialCall(TFunction<void(TArray<Gs2::SerialKey::Model::FSerialKeyPtr>)> Callback,const FString CampaignModelName,const TOptional<FString> IssueJobName)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeSerialKeysWithInitialCallTask>>(this->AsShared(), Callback, CampaignModelName, IssueJobName);
    }

    TSharedPtr<Gs2::SerialKey::Domain::Model::FSerialKeyDomain> FUserDomain::SerialKey(
        const FString SerialKeyCode
    )
    {
        return MakeShared<Gs2::SerialKey::Domain::Model::FSerialKeyDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId,
            SerialKeyCode == TEXT("") ? TOptional<FString>() : TOptional<FString>(SerialKeyCode)
        );
    }

    FString FUserDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            ChildType;
    }

    FString FUserDomain::CreateCacheKey(
        TOptional<FString> UserId
    )
    {
        return FString("") +
            (UserId.IsSet() ? *UserId : "null");
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif
