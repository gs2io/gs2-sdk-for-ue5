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

#include "Stamina/Domain/Model/StaminaAccessToken.h"
#include "Stamina/Domain/Model/Stamina.h"
#include "Stamina/Domain/Model/Namespace.h"
#include "Stamina/Domain/Model/StaminaModelMaster.h"
#include "Stamina/Domain/Model/MaxStaminaTableMaster.h"
#include "Stamina/Domain/Model/RecoverIntervalTableMaster.h"
#include "Stamina/Domain/Model/RecoverValueTableMaster.h"
#include "Stamina/Domain/Model/CurrentStaminaMaster.h"
#include "Stamina/Domain/Model/StaminaModel.h"
#include "Stamina/Domain/Model/Stamina.h"
#include "Stamina/Domain/Model/StaminaAccessToken.h"
#include "Stamina/Domain/Model/User.h"
#include "Stamina/Domain/Model/UserAccessToken.h"
#include "Stamina/Model/Cache/Stamina.h"
#include "Stamina/Model/Cache/StaminaModel.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::Stamina::Domain::Model
{

    FStaminaAccessTokenDomain::FStaminaAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Stamina::Domain::FGs2StaminaDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const TOptional<FString> StaminaName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Stamina::FGs2StaminaRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        StaminaName(StaminaName),
        ParentKey(Gs2::Stamina::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId(),
            "Stamina"
        ))
    {
    }

    FStaminaAccessTokenDomain::FStaminaAccessTokenDomain(
        const FStaminaAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        StaminaName(From.StaminaName),
        ParentKey(From.ParentKey)
    {

    }

    FStaminaAccessTokenDomain::FGetTask::FGetTask(
        const TSharedPtr<FStaminaAccessTokenDomain>& Self,
        const Request::FGetStaminaRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStaminaAccessTokenDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStaminaAccessTokenDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Stamina::Model::FStamina>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithStaminaName(Self->StaminaName)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto CacheOwnerSnapshotUserId = Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>();
        const auto CacheOwnerSnapshotTimeOffset = Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>();
        const auto Future = Self->Client->GetStamina(
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
              }if (!((CacheOwnerSnapshotUserId)).IsSet())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("userId"), TEXT("userId is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }
        Gs2::Stamina::Model::Cache::FStaminaCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            (CacheOwnerSnapshotUserId),
            ResultModel->GetItem()->GetStaminaName(),
            CacheOwnerSnapshotTimeOffset,
            ResultModel->GetItem()
        );
            }
            if (ResultModel.IsValid() && ResultModel->GetStaminaModel() != nullptr)
            {

        if (!ResultModel.IsValid() || !ResultModel->GetItem().IsValid())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("result.item"), TEXT("result.item is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }
        Gs2::Stamina::Model::Cache::FStaminaModelCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetStaminaName(),
            CacheOwnerSnapshotTimeOffset,
            ResultModel->GetStaminaModel()
        );
            }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStaminaAccessTokenDomain::FGetTask>> FStaminaAccessTokenDomain::Get(
        Request::FGetStaminaRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FStaminaAccessTokenDomain::FConsumeTask::FConsumeTask(
        const TSharedPtr<FStaminaAccessTokenDomain>& Self,
        const Request::FConsumeStaminaRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStaminaAccessTokenDomain::FConsumeTask::FConsumeTask(
        const FConsumeTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStaminaAccessTokenDomain::FConsumeTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FStaminaAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithStaminaName(Self->StaminaName)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto CacheOwnerSnapshotUserId = Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>();
        const auto CacheOwnerSnapshotTimeOffset = Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>();
        const auto Future = Self->Client->ConsumeStamina(
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
              }if (!((CacheOwnerSnapshotUserId)).IsSet())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("userId"), TEXT("userId is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }
        Gs2::Stamina::Model::Cache::FStaminaCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            (CacheOwnerSnapshotUserId),
            ResultModel->GetItem()->GetStaminaName(),
            CacheOwnerSnapshotTimeOffset,
            ResultModel->GetItem()
        );
            }
            if (ResultModel.IsValid() && ResultModel->GetStaminaModel() != nullptr)
            {

        if (!ResultModel.IsValid() || !ResultModel->GetItem().IsValid())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("result.item"), TEXT("result.item is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }
        Gs2::Stamina::Model::Cache::FStaminaModelCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetStaminaName(),
            CacheOwnerSnapshotTimeOffset,
            ResultModel->GetStaminaModel()
        );
            }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStaminaAccessTokenDomain::FConsumeTask>> FStaminaAccessTokenDomain::Consume(
        Request::FConsumeStaminaRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FConsumeTask>>(this->AsShared(), Request);
    }

    FStaminaAccessTokenDomain::FApplyTask::FApplyTask(
        const TSharedPtr<FStaminaAccessTokenDomain>& Self,
        const Request::FApplyStaminaRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStaminaAccessTokenDomain::FApplyTask::FApplyTask(
        const FApplyTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStaminaAccessTokenDomain::FApplyTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FStaminaAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithStaminaName(Self->StaminaName)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto CacheOwnerSnapshotUserId = Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>();
        const auto CacheOwnerSnapshotTimeOffset = Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>();
        const auto Future = Self->Client->ApplyStamina(
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
              }if (!((CacheOwnerSnapshotUserId)).IsSet())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("userId"), TEXT("userId is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }
        Gs2::Stamina::Model::Cache::FStaminaCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            (CacheOwnerSnapshotUserId),
            ResultModel->GetItem()->GetStaminaName(),
            CacheOwnerSnapshotTimeOffset,
            ResultModel->GetItem()
        );
            }
            if (ResultModel.IsValid() && ResultModel->GetStaminaModel() != nullptr)
            {

        if (!ResultModel.IsValid() || !ResultModel->GetItem().IsValid())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("result.item"), TEXT("result.item is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }
        Gs2::Stamina::Model::Cache::FStaminaModelCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetStaminaName(),
            CacheOwnerSnapshotTimeOffset,
            ResultModel->GetStaminaModel()
        );
            }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStaminaAccessTokenDomain::FApplyTask>> FStaminaAccessTokenDomain::Apply(
        Request::FApplyStaminaRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FApplyTask>>(this->AsShared(), Request);
    }

    FStaminaAccessTokenDomain::FDecreaseMaxValueTask::FDecreaseMaxValueTask(
        const TSharedPtr<FStaminaAccessTokenDomain>& Self,
        const Request::FDecreaseMaxValueRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStaminaAccessTokenDomain::FDecreaseMaxValueTask::FDecreaseMaxValueTask(
        const FDecreaseMaxValueTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStaminaAccessTokenDomain::FDecreaseMaxValueTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FStaminaAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithStaminaName(Self->StaminaName)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto CacheOwnerSnapshotUserId = Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>();
        const auto CacheOwnerSnapshotTimeOffset = Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>();
        const auto Future = Self->Client->DecreaseMaxValue(
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
              }if (!((CacheOwnerSnapshotUserId)).IsSet())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("userId"), TEXT("userId is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }
        Gs2::Stamina::Model::Cache::FStaminaCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            (CacheOwnerSnapshotUserId),
            ResultModel->GetItem()->GetStaminaName(),
            CacheOwnerSnapshotTimeOffset,
            ResultModel->GetItem()
        );
            }
            if (ResultModel.IsValid() && ResultModel->GetStaminaModel() != nullptr)
            {

        if (!ResultModel.IsValid() || !ResultModel->GetItem().IsValid())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("result.item"), TEXT("result.item is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }
        Gs2::Stamina::Model::Cache::FStaminaModelCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetStaminaName(),
            CacheOwnerSnapshotTimeOffset,
            ResultModel->GetStaminaModel()
        );
            }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStaminaAccessTokenDomain::FDecreaseMaxValueTask>> FStaminaAccessTokenDomain::DecreaseMaxValue(
        Request::FDecreaseMaxValueRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDecreaseMaxValueTask>>(this->AsShared(), Request);
    }

    FStaminaAccessTokenDomain::FSetMaxValueByStatusTask::FSetMaxValueByStatusTask(
        const TSharedPtr<FStaminaAccessTokenDomain>& Self,
        const Request::FSetMaxValueByStatusRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStaminaAccessTokenDomain::FSetMaxValueByStatusTask::FSetMaxValueByStatusTask(
        const FSetMaxValueByStatusTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStaminaAccessTokenDomain::FSetMaxValueByStatusTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FStaminaAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithStaminaName(Self->StaminaName)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto CacheOwnerSnapshotUserId = Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>();
        const auto CacheOwnerSnapshotTimeOffset = Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>();
        const auto Future = Self->Client->SetMaxValueByStatus(
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
              }if (!((CacheOwnerSnapshotUserId)).IsSet())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("userId"), TEXT("userId is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }
        Gs2::Stamina::Model::Cache::FStaminaCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            (CacheOwnerSnapshotUserId),
            ResultModel->GetItem()->GetStaminaName(),
            CacheOwnerSnapshotTimeOffset,
            ResultModel->GetItem()
        );
            }
            if (ResultModel.IsValid() && ResultModel->GetStaminaModel() != nullptr)
            {

        if (!ResultModel.IsValid() || !ResultModel->GetItem().IsValid())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("result.item"), TEXT("result.item is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }
        Gs2::Stamina::Model::Cache::FStaminaModelCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetStaminaName(),
            CacheOwnerSnapshotTimeOffset,
            ResultModel->GetStaminaModel()
        );
            }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStaminaAccessTokenDomain::FSetMaxValueByStatusTask>> FStaminaAccessTokenDomain::SetMaxValueByStatus(
        Request::FSetMaxValueByStatusRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FSetMaxValueByStatusTask>>(this->AsShared(), Request);
    }

    FStaminaAccessTokenDomain::FSetRecoverIntervalByStatusTask::FSetRecoverIntervalByStatusTask(
        const TSharedPtr<FStaminaAccessTokenDomain>& Self,
        const Request::FSetRecoverIntervalByStatusRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStaminaAccessTokenDomain::FSetRecoverIntervalByStatusTask::FSetRecoverIntervalByStatusTask(
        const FSetRecoverIntervalByStatusTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStaminaAccessTokenDomain::FSetRecoverIntervalByStatusTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FStaminaAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithStaminaName(Self->StaminaName)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto CacheOwnerSnapshotUserId = Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>();
        const auto CacheOwnerSnapshotTimeOffset = Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>();
        const auto Future = Self->Client->SetRecoverIntervalByStatus(
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
              }if (!((CacheOwnerSnapshotUserId)).IsSet())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("userId"), TEXT("userId is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }
        Gs2::Stamina::Model::Cache::FStaminaCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            (CacheOwnerSnapshotUserId),
            ResultModel->GetItem()->GetStaminaName(),
            CacheOwnerSnapshotTimeOffset,
            ResultModel->GetItem()
        );
            }
            if (ResultModel.IsValid() && ResultModel->GetStaminaModel() != nullptr)
            {

        if (!ResultModel.IsValid() || !ResultModel->GetItem().IsValid())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("result.item"), TEXT("result.item is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }
        Gs2::Stamina::Model::Cache::FStaminaModelCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetStaminaName(),
            CacheOwnerSnapshotTimeOffset,
            ResultModel->GetStaminaModel()
        );
            }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStaminaAccessTokenDomain::FSetRecoverIntervalByStatusTask>> FStaminaAccessTokenDomain::SetRecoverIntervalByStatus(
        Request::FSetRecoverIntervalByStatusRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FSetRecoverIntervalByStatusTask>>(this->AsShared(), Request);
    }

    FStaminaAccessTokenDomain::FSetRecoverValueByStatusTask::FSetRecoverValueByStatusTask(
        const TSharedPtr<FStaminaAccessTokenDomain>& Self,
        const Request::FSetRecoverValueByStatusRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStaminaAccessTokenDomain::FSetRecoverValueByStatusTask::FSetRecoverValueByStatusTask(
        const FSetRecoverValueByStatusTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStaminaAccessTokenDomain::FSetRecoverValueByStatusTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FStaminaAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithStaminaName(Self->StaminaName)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto CacheOwnerSnapshotUserId = Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>();
        const auto CacheOwnerSnapshotTimeOffset = Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>();
        const auto Future = Self->Client->SetRecoverValueByStatus(
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
              }if (!((CacheOwnerSnapshotUserId)).IsSet())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("userId"), TEXT("userId is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }
        Gs2::Stamina::Model::Cache::FStaminaCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            (CacheOwnerSnapshotUserId),
            ResultModel->GetItem()->GetStaminaName(),
            CacheOwnerSnapshotTimeOffset,
            ResultModel->GetItem()
        );
            }
            if (ResultModel.IsValid() && ResultModel->GetStaminaModel() != nullptr)
            {

        if (!ResultModel.IsValid() || !ResultModel->GetItem().IsValid())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("result.item"), TEXT("result.item is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }
        Gs2::Stamina::Model::Cache::FStaminaModelCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetStaminaName(),
            CacheOwnerSnapshotTimeOffset,
            ResultModel->GetStaminaModel()
        );
            }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStaminaAccessTokenDomain::FSetRecoverValueByStatusTask>> FStaminaAccessTokenDomain::SetRecoverValueByStatus(
        Request::FSetRecoverValueByStatusRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FSetRecoverValueByStatusTask>>(this->AsShared(), Request);
    }

    FStaminaAccessTokenDomain::FVerifyValueTask::FVerifyValueTask(
        const TSharedPtr<FStaminaAccessTokenDomain>& Self,
        const Request::FVerifyStaminaValueRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStaminaAccessTokenDomain::FVerifyValueTask::FVerifyValueTask(
        const FVerifyValueTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStaminaAccessTokenDomain::FVerifyValueTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FStaminaAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithStaminaName(Self->StaminaName);
        const auto CacheOwnerSnapshotUserId = Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>();
        const auto CacheOwnerSnapshotTimeOffset = Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>();
        const auto Future = Self->Client->VerifyStaminaValue(
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
              }if (!((CacheOwnerSnapshotUserId)).IsSet())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("userId"), TEXT("userId is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }
        Gs2::Stamina::Model::Cache::FStaminaCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            (CacheOwnerSnapshotUserId),
            ResultModel->GetItem()->GetStaminaName(),
            CacheOwnerSnapshotTimeOffset,
            ResultModel->GetItem()
        );
            }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStaminaAccessTokenDomain::FVerifyValueTask>> FStaminaAccessTokenDomain::VerifyValue(
        Request::FVerifyStaminaValueRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FVerifyValueTask>>(this->AsShared(), Request);
    }

    FStaminaAccessTokenDomain::FVerifyMaxValueTask::FVerifyMaxValueTask(
        const TSharedPtr<FStaminaAccessTokenDomain>& Self,
        const Request::FVerifyStaminaMaxValueRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStaminaAccessTokenDomain::FVerifyMaxValueTask::FVerifyMaxValueTask(
        const FVerifyMaxValueTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStaminaAccessTokenDomain::FVerifyMaxValueTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FStaminaAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithStaminaName(Self->StaminaName);
        const auto CacheOwnerSnapshotUserId = Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>();
        const auto CacheOwnerSnapshotTimeOffset = Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>();
        const auto Future = Self->Client->VerifyStaminaMaxValue(
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
              }if (!((CacheOwnerSnapshotUserId)).IsSet())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("userId"), TEXT("userId is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }
        Gs2::Stamina::Model::Cache::FStaminaCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            (CacheOwnerSnapshotUserId),
            ResultModel->GetItem()->GetStaminaName(),
            CacheOwnerSnapshotTimeOffset,
            ResultModel->GetItem()
        );
            }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStaminaAccessTokenDomain::FVerifyMaxValueTask>> FStaminaAccessTokenDomain::VerifyMaxValue(
        Request::FVerifyStaminaMaxValueRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FVerifyMaxValueTask>>(this->AsShared(), Request);
    }

    FStaminaAccessTokenDomain::FVerifyRecoverIntervalMinutesTask::FVerifyRecoverIntervalMinutesTask(
        const TSharedPtr<FStaminaAccessTokenDomain>& Self,
        const Request::FVerifyStaminaRecoverIntervalMinutesRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStaminaAccessTokenDomain::FVerifyRecoverIntervalMinutesTask::FVerifyRecoverIntervalMinutesTask(
        const FVerifyRecoverIntervalMinutesTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStaminaAccessTokenDomain::FVerifyRecoverIntervalMinutesTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FStaminaAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithStaminaName(Self->StaminaName);
        const auto CacheOwnerSnapshotUserId = Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>();
        const auto CacheOwnerSnapshotTimeOffset = Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>();
        const auto Future = Self->Client->VerifyStaminaRecoverIntervalMinutes(
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
              }if (!((CacheOwnerSnapshotUserId)).IsSet())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("userId"), TEXT("userId is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }
        Gs2::Stamina::Model::Cache::FStaminaCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            (CacheOwnerSnapshotUserId),
            ResultModel->GetItem()->GetStaminaName(),
            CacheOwnerSnapshotTimeOffset,
            ResultModel->GetItem()
        );
            }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStaminaAccessTokenDomain::FVerifyRecoverIntervalMinutesTask>> FStaminaAccessTokenDomain::VerifyRecoverIntervalMinutes(
        Request::FVerifyStaminaRecoverIntervalMinutesRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FVerifyRecoverIntervalMinutesTask>>(this->AsShared(), Request);
    }

    FStaminaAccessTokenDomain::FVerifyRecoverValueTask::FVerifyRecoverValueTask(
        const TSharedPtr<FStaminaAccessTokenDomain>& Self,
        const Request::FVerifyStaminaRecoverValueRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStaminaAccessTokenDomain::FVerifyRecoverValueTask::FVerifyRecoverValueTask(
        const FVerifyRecoverValueTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStaminaAccessTokenDomain::FVerifyRecoverValueTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FStaminaAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithStaminaName(Self->StaminaName);
        const auto CacheOwnerSnapshotUserId = Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>();
        const auto CacheOwnerSnapshotTimeOffset = Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>();
        const auto Future = Self->Client->VerifyStaminaRecoverValue(
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
              }if (!((CacheOwnerSnapshotUserId)).IsSet())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("userId"), TEXT("userId is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }
        Gs2::Stamina::Model::Cache::FStaminaCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            (CacheOwnerSnapshotUserId),
            ResultModel->GetItem()->GetStaminaName(),
            CacheOwnerSnapshotTimeOffset,
            ResultModel->GetItem()
        );
            }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStaminaAccessTokenDomain::FVerifyRecoverValueTask>> FStaminaAccessTokenDomain::VerifyRecoverValue(
        Request::FVerifyStaminaRecoverValueRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FVerifyRecoverValueTask>>(this->AsShared(), Request);
    }

    FStaminaAccessTokenDomain::FVerifyOverflowValueTask::FVerifyOverflowValueTask(
        const TSharedPtr<FStaminaAccessTokenDomain>& Self,
        const Request::FVerifyStaminaOverflowValueRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStaminaAccessTokenDomain::FVerifyOverflowValueTask::FVerifyOverflowValueTask(
        const FVerifyOverflowValueTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStaminaAccessTokenDomain::FVerifyOverflowValueTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FStaminaAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithStaminaName(Self->StaminaName);
        const auto CacheOwnerSnapshotUserId = Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>();
        const auto CacheOwnerSnapshotTimeOffset = Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>();
        const auto Future = Self->Client->VerifyStaminaOverflowValue(
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
              }if (!((CacheOwnerSnapshotUserId)).IsSet())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("userId"), TEXT("userId is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }
        Gs2::Stamina::Model::Cache::FStaminaCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            (CacheOwnerSnapshotUserId),
            ResultModel->GetItem()->GetStaminaName(),
            CacheOwnerSnapshotTimeOffset,
            ResultModel->GetItem()
        );
            }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStaminaAccessTokenDomain::FVerifyOverflowValueTask>> FStaminaAccessTokenDomain::VerifyOverflowValue(
        Request::FVerifyStaminaOverflowValueRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FVerifyOverflowValueTask>>(this->AsShared(), Request);
    }

    FString FStaminaAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> StaminaName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (StaminaName.IsSet() ? *StaminaName : "null") + ":" +
            ChildType;
    }

    FString FStaminaAccessTokenDomain::CreateCacheKey(
        TOptional<FString> StaminaName
    )
    {
        return FString("") +
            (StaminaName.IsSet() ? *StaminaName : "null");
    }

    FStaminaAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FStaminaAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FStaminaAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FStaminaAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Stamina::Model::FStamina>> Result
    )
    {
        const auto CacheParentKey = Gs2::Stamina::Model::Cache::FStaminaCache::CreateCacheParentKey(

            Self->NamespaceName,
            Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>(),
            Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>()
        );
        const auto CacheKey = Gs2::Stamina::Model::Cache::FStaminaCache::CreateCacheKey(

            Self->StaminaName
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Stamina::Model::FStamina::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Stamina::Model::FStaminaPtr Value;
                const auto CacheHit = Gs2::Stamina::Model::Cache::FStaminaCache::TryGet(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>(),
                    Self->StaminaName,
                    Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>(),
                    &Value
                );
                if (CacheHit)
                {
                    *Result = Value;
                    return nullptr;
                }
                const auto Error = Gs2::Stamina::Model::Cache::FStaminaCache::Fetch(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>(),
                    Self->StaminaName,
                    Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>(),
                    [Self](Gs2::Stamina::Model::FStaminaPtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::Stamina::Request::FGetStaminaRequest>()
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

    TSharedPtr<FAsyncTask<FStaminaAccessTokenDomain::FModelTask>> FStaminaAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FStaminaAccessTokenDomain::FModelTask>>(this->AsShared());
    }

    void FStaminaAccessTokenDomain::Invalidate()
    {
        Gs2::Stamina::Model::Cache::FStaminaCache::Delete(
            Gs2->Cache,

            NamespaceName,
            AccessToken.IsValid() ? UserId() : TOptional<FString>(),
            StaminaName,
            AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
        );
    }

    FStaminaAccessTokenDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FStaminaAccessTokenDomain>& Self,
        TFunction<void(Gs2::Stamina::Model::FStaminaPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FStaminaAccessTokenDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStaminaAccessTokenDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FStaminaAccessTokenDomain::FSubscribeWithInitialCallTask>> FStaminaAccessTokenDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Stamina::Model::FStaminaPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FStaminaAccessTokenDomain::Subscribe(
        TFunction<void(Gs2::Stamina::Model::FStaminaPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Stamina::Model::Cache::FStaminaCache::CreateCacheParentKey(

            NamespaceName,
            AccessToken.IsValid() ? UserId() : TOptional<FString>(),
            AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Stamina::Model::Cache::FStaminaCache::CreateCacheKey(

            StaminaName
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Stamina::Domain::FGs2StaminaDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryStaminaName = StaminaName;
        const auto SourceToken = AccessToken;
        const TOptional<FString> RegisteredUserId = SourceToken.IsValid()
            ? TOptional<FString>(SourceToken->GetUserId())
            : TOptional<FString>();
        const int32 RegisteredTimeOffset = SourceToken.IsValid() ? SourceToken->GetTimeOffset().Get(0) : 0;
        return Gs2->Cache->Subscribe(
            Gs2::Stamina::Model::FStamina::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Stamina::Model::FStamina>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryStaminaName, SourceToken, RegisteredUserId, RegisteredTimeOffset]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid() || !SourceToken.IsValid() || !RegisteredUserId.IsSet())
                {
                    return;
                }
                const auto TokenSnapshot = MakeShared<Gs2::Auth::Model::FAccessToken>(*SourceToken);
                if (TokenSnapshot->GetUserId() != RegisteredUserId || TokenSnapshot->GetTimeOffset().Get(0) != RegisteredTimeOffset)
                {
                    return;
                }
                const auto Domain = MakeShared<FStaminaAccessTokenDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    TokenSnapshot,
                    QueryStaminaName
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FStaminaAccessTokenDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Stamina::Model::Cache::FStaminaCache::CreateCacheParentKey(

            NamespaceName,
            AccessToken.IsValid() ? UserId() : TOptional<FString>(),
            AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Stamina::Model::Cache::FStaminaCache::CreateCacheKey(

            StaminaName
        );
        Gs2->Cache->Unsubscribe(
            Gs2::Stamina::Model::FStamina::TypeName,
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
