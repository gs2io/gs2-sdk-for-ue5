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

#include "Formation/Domain/Model/Form.h"
#include "Formation/Domain/Model/Namespace.h"
#include "Formation/Domain/Model/FormModel.h"
#include "Formation/Domain/Model/FormModelMaster.h"
#include "Formation/Domain/Model/MoldModel.h"
#include "Formation/Domain/Model/MoldModelMaster.h"
#include "Formation/Domain/Model/PropertyFormModel.h"
#include "Formation/Domain/Model/PropertyFormModelMaster.h"
#include "Formation/Domain/Model/CurrentFormMaster.h"
#include "Formation/Domain/Model/Mold.h"
#include "Formation/Domain/Model/MoldAccessToken.h"
#include "Formation/Domain/Model/Form.h"
#include "Formation/Domain/Model/FormAccessToken.h"
#include "Formation/Domain/Model/PropertyForm.h"
#include "Formation/Domain/Model/PropertyFormAccessToken.h"
#include "Formation/Domain/Model/User.h"
#include "Formation/Domain/Model/UserAccessToken.h"
#include "Formation/Model/Cache/Form.h"
#include "Formation/Model/Cache/Mold.h"
#include "Formation/Model/Cache/MoldModel.h"
#include "Formation/Model/Cache/FormModel.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Formation::Domain::Model
{

    FFormDomain::FFormDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Formation::Domain::FGs2FormationDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<FString> MoldModelName,
        const TOptional<int32> Index
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Formation::FGs2FormationRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        MoldModelName(MoldModelName),
        Index(Index),
        ParentKey(Gs2::Formation::Domain::Model::FMoldDomain::CreateCacheParentKey(
            NamespaceName,
            UserId,
            MoldModelName,
            "Form"
        ))
    {
    }

    FFormDomain::FFormDomain(
        const FFormDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        MoldModelName(From.MoldModelName),
        Index(From.Index),
        ParentKey(From.ParentKey)
    {

    }

    FFormDomain::FGetTask::FGetTask(
        const TSharedPtr<FFormDomain>& Self,
        const Request::FGetFormByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FFormDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FFormDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Formation::Model::FForm>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithMoldModelName(Self->MoldModelName)
            ->WithIndex(Self->Index);
        const auto Future = Self->Client->GetFormByUserId(
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
              }if (!(Request->GetUserId()).IsSet())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("userId"), TEXT("userId is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }
        Gs2::Formation::Model::Cache::FFormCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetUserId(),
            Request->GetMoldModelName(),
            ResultModel->GetItem()->GetIndex().Get(int32{}),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
            if (ResultModel.IsValid() && ResultModel->GetMold() != nullptr)
            {

        if (!(Request->GetUserId()).IsSet())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("userId"), TEXT("userId is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }
        Gs2::Formation::Model::Cache::FMoldCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetUserId(),
            Request->GetMoldModelName(),
            TOptional<int32>(),
            ResultModel->GetMold()
        );
            }
            if (ResultModel.IsValid() && ResultModel->GetMoldModel() != nullptr)
            {


        Gs2::Formation::Model::Cache::FMoldModelCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetMoldModelName(),
            TOptional<int32>(),
            ResultModel->GetMoldModel()
        );
            }
            if (ResultModel.IsValid() && ResultModel->GetFormModel() != nullptr)
            {


        Gs2::Formation::Model::Cache::FFormModelCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetMoldModelName(),
            TOptional<int32>(),
            ResultModel->GetFormModel()
        );
            }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FFormDomain::FGetTask>> FFormDomain::Get(
        Request::FGetFormByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FFormDomain::FGetWithSignatureTask::FGetWithSignatureTask(
        const TSharedPtr<FFormDomain>& Self,
        const Request::FGetFormWithSignatureByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FFormDomain::FGetWithSignatureTask::FGetWithSignatureTask(
        const FGetWithSignatureTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FFormDomain::FGetWithSignatureTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Formation::Domain::Model::FFormDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithMoldModelName(Self->MoldModelName)
            ->WithIndex(Self->Index);
        const auto Future = Self->Client->GetFormWithSignatureByUserId(
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
              }if (!(Request->GetUserId()).IsSet())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("userId"), TEXT("userId is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }
        Gs2::Formation::Model::Cache::FFormCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetUserId(),
            Request->GetMoldModelName(),
            ResultModel->GetItem()->GetIndex().Get(int32{}),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
            if (ResultModel.IsValid() && ResultModel->GetMold() != nullptr)
            {

        if (!(Request->GetUserId()).IsSet())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("userId"), TEXT("userId is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }
        Gs2::Formation::Model::Cache::FMoldCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetUserId(),
            Request->GetMoldModelName(),
            TOptional<int32>(),
            ResultModel->GetMold()
        );
            }
            if (ResultModel.IsValid() && ResultModel->GetMoldModel() != nullptr)
            {


        Gs2::Formation::Model::Cache::FMoldModelCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetMoldModelName(),
            TOptional<int32>(),
            ResultModel->GetMoldModel()
        );
            }
            if (ResultModel.IsValid() && ResultModel->GetFormModel() != nullptr)
            {


        Gs2::Formation::Model::Cache::FFormModelCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetMoldModelName(),
            TOptional<int32>(),
            ResultModel->GetFormModel()
        );
            }
        auto Domain = Self;
        if (ResultModel != nullptr)
        {
            if (ResultModel->GetBody().IsSet())
            {
                Domain->Body = *ResultModel->GetBody();
            }
            if (ResultModel->GetSignature().IsSet())
            {
                Domain->Signature = *ResultModel->GetSignature();
            }
        }

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FFormDomain::FGetWithSignatureTask>> FFormDomain::GetWithSignature(
        Request::FGetFormWithSignatureByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetWithSignatureTask>>(this->AsShared(), Request);
    }

    FFormDomain::FSetTask::FSetTask(
        const TSharedPtr<FFormDomain>& Self,
        const Request::FSetFormByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FFormDomain::FSetTask::FSetTask(
        const FSetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FFormDomain::FSetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Formation::Domain::Model::FFormDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithMoldModelName(Self->MoldModelName)
            ->WithIndex(Self->Index);
        const auto Future = Self->Client->SetFormByUserId(
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
              }if (!(Request->GetUserId()).IsSet())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("userId"), TEXT("userId is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }
        Gs2::Formation::Model::Cache::FFormCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetUserId(),
            Request->GetMoldModelName(),
            ResultModel->GetItem()->GetIndex().Get(int32{}),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
            if (ResultModel.IsValid() && ResultModel->GetMold() != nullptr)
            {

        if (!(Request->GetUserId()).IsSet())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("userId"), TEXT("userId is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }
        Gs2::Formation::Model::Cache::FMoldCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetUserId(),
            Request->GetMoldModelName(),
            TOptional<int32>(),
            ResultModel->GetMold()
        );
            }
            if (ResultModel.IsValid() && ResultModel->GetMoldModel() != nullptr)
            {


        Gs2::Formation::Model::Cache::FMoldModelCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetMoldModelName(),
            TOptional<int32>(),
            ResultModel->GetMoldModel()
        );
            }
            if (ResultModel.IsValid() && ResultModel->GetFormModel() != nullptr)
            {


        Gs2::Formation::Model::Cache::FFormModelCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetMoldModelName(),
            TOptional<int32>(),
            ResultModel->GetFormModel()
        );
            }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FFormDomain::FSetTask>> FFormDomain::Set(
        Request::FSetFormByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FSetTask>>(this->AsShared(), Request);
    }

    FFormDomain::FAcquireActionsToPropertiesTask::FAcquireActionsToPropertiesTask(
        const TSharedPtr<FFormDomain>& Self,
        const Request::FAcquireActionsToFormPropertiesRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FFormDomain::FAcquireActionsToPropertiesTask::FAcquireActionsToPropertiesTask(
        const FAcquireActionsToPropertiesTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FFormDomain::FAcquireActionsToPropertiesTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::FTransactionDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithMoldModelName(Self->MoldModelName)
            ->WithIndex(Self->Index);
        const auto Future = Self->Client->AcquireActionsToFormProperties(
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
              }if (!(Request->GetUserId()).IsSet())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("userId"), TEXT("userId is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }
        Gs2::Formation::Model::Cache::FFormCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetUserId(),
            Request->GetMoldModelName(),
            ResultModel->GetItem()->GetIndex().Get(int32{}),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
            if (ResultModel.IsValid() && ResultModel->GetMold() != nullptr)
            {

        if (!(Request->GetUserId()).IsSet())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("userId"), TEXT("userId is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }
        Gs2::Formation::Model::Cache::FMoldCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetUserId(),
            Request->GetMoldModelName(),
            TOptional<int32>(),
            ResultModel->GetMold()
        );
            }
        const auto Transaction = Gs2::Core::Domain::Internal::FTransactionDomainFactory::ToTransaction(
            Self->Gs2,
            *Self->UserId,
            ResultModel->GetAutoRunStampSheet().IsSet() ? *ResultModel->GetAutoRunStampSheet() : false,
            ResultModel->GetTransactionId().IsSet() ? *ResultModel->GetTransactionId() : FString(),
            ResultModel->GetStampSheet().IsSet() ? *ResultModel->GetStampSheet() : FString(),
            ResultModel->GetStampSheetEncryptionKeyId().IsSet() ? *ResultModel->GetStampSheetEncryptionKeyId() : FString(),
            ResultModel->GetAtomicCommit().IsSet() ? *ResultModel->GetAtomicCommit() : false,
            ResultModel->GetTransactionResult()
        );
        const auto Future3 = Transaction->Wait(true);
        Future3->StartSynchronousTask();
        if (Future3->GetTask().IsError())
        {
            return Future3->GetTask().Error();
        }
        *Result = Transaction;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FFormDomain::FAcquireActionsToPropertiesTask>> FFormDomain::AcquireActionsToProperties(
        Request::FAcquireActionsToFormPropertiesRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FAcquireActionsToPropertiesTask>>(this->AsShared(), Request);
    }

    FFormDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FFormDomain>& Self,
        const Request::FDeleteFormByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FFormDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FFormDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Formation::Domain::Model::FFormDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithMoldModelName(Self->MoldModelName)
            ->WithIndex(Self->Index);
        const auto Future = Self->Client->DeleteFormByUserId(
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

              if (!ResultModel.IsValid() || !ResultModel->GetItem().IsValid())
                  {
                    const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                      Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("result.item"), TEXT("result.item is invalid."), TEXT("invalid_response")));
                      return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
                    }if (!(Request->GetUserId()).IsSet())
                  {
                    const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                      Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("userId"), TEXT("userId is invalid."), TEXT("invalid_response")));
                      return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
                    }
              Gs2::Formation::Model::Cache::FFormCache::Delete(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetUserId(),
            Request->GetMoldModelName(),
            ResultModel->GetItem()->GetIndex().Get(int32{}),
            TOptional<int32>()
        );
              if (!(Request->GetUserId()).IsSet())
                  {
                    const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                      Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("userId"), TEXT("userId is invalid."), TEXT("invalid_response")));
                      return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
                    }
              Gs2::Formation::Model::Cache::FMoldCache::Delete(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetUserId(),
            Request->GetMoldModelName(),
            TOptional<int32>()
        );

              Gs2::Formation::Model::Cache::FMoldModelCache::Delete(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetMoldModelName(),
            TOptional<int32>()
        );

              Gs2::Formation::Model::Cache::FFormModelCache::Delete(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetMoldModelName(),
            TOptional<int32>()
        );
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FFormDomain::FDeleteTask>> FFormDomain::Delete(
        Request::FDeleteFormByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FFormDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> MoldModelName,
        TOptional<int32> Index,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (MoldModelName.IsSet() ? *MoldModelName : "null") + ":" +
            (Index.IsSet() ? FString::FromInt(*Index) : "null") + ":" +
            ChildType;
    }

    FString FFormDomain::CreateCacheKey(
        TOptional<int32> Index
    )
    {
        return FString("") +
            (Index.IsSet() ? FString::FromInt(*Index) : "null");
    }

    FFormDomain::FModelTask::FModelTask(
        const TSharedPtr<FFormDomain> Self
    ): Self(Self)
    {

    }

    FFormDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FFormDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Formation::Model::FForm>> Result
    )
    {
        const auto CacheParentKey = Gs2::Formation::Model::Cache::FFormCache::CreateCacheParentKey(

            Self->NamespaceName,
            Self->UserId,
            Self->MoldModelName,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::Formation::Model::Cache::FFormCache::CreateCacheKey(

            Self->Index
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Formation::Model::FForm::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Formation::Model::FFormPtr Value;
                const auto CacheHit = Gs2::Formation::Model::Cache::FFormCache::TryGet(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->UserId,
                    Self->MoldModelName,
                    Self->Index,
                    TOptional<int32>(),
                    &Value
                );
                if (CacheHit)
                {
                    *Result = Value;
                    return nullptr;
                }
                const auto Error = Gs2::Formation::Model::Cache::FFormCache::Fetch(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->UserId,
                    Self->MoldModelName,
                    Self->Index,
                    TOptional<int32>(),
                    [Self](Gs2::Formation::Model::FFormPtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::Formation::Request::FGetFormByUserIdRequest>()
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

    TSharedPtr<FAsyncTask<FFormDomain::FModelTask>> FFormDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FFormDomain::FModelTask>>(this->AsShared());
    }

    void FFormDomain::Invalidate()
    {
        Gs2::Formation::Model::Cache::FFormCache::Delete(
            Gs2->Cache,

            NamespaceName,
            UserId,
            MoldModelName,
            Index,
            TOptional<int32>()
        );
    }

    FFormDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FFormDomain>& Self,
        TFunction<void(Gs2::Formation::Model::FFormPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FFormDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FFormDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FFormDomain::FSubscribeWithInitialCallTask>> FFormDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Formation::Model::FFormPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FFormDomain::Subscribe(
        TFunction<void(Gs2::Formation::Model::FFormPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Formation::Model::Cache::FFormCache::CreateCacheParentKey(

            NamespaceName,
            UserId,
            MoldModelName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Formation::Model::Cache::FFormCache::CreateCacheKey(

            Index
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Formation::Domain::FGs2FormationDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryUserId = UserId;
        const TOptional<FString> QueryMoldModelName = MoldModelName;
        const TOptional<int32> QueryIndex = Index;
        return Gs2->Cache->Subscribe(
            Gs2::Formation::Model::FForm::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Formation::Model::FForm>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryUserId, QueryMoldModelName, QueryIndex]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FFormDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    QueryUserId,
                    QueryMoldModelName,
                    QueryIndex
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FFormDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Formation::Model::Cache::FFormCache::CreateCacheParentKey(

            NamespaceName,
            UserId,
            MoldModelName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Formation::Model::Cache::FFormCache::CreateCacheKey(

            Index
        );
        Gs2->Cache->Unsubscribe(
            Gs2::Formation::Model::FForm::TypeName,
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
