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

#include "Formation/Domain/Model/Mold.h"
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
#include "Formation/Model/Cache/Mold.h"
#include "Formation/Model/Cache/MoldModel.h"
#include "Formation/Model/Cache/Form.h"
#include "Formation/Model/Cache/FormModel.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Formation::Domain::Model
{

    FMoldDomain::FMoldDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Formation::Domain::FGs2FormationDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<FString> MoldModelName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Formation::FGs2FormationRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        MoldModelName(MoldModelName),
        ParentKey(Gs2::Formation::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId,
            "Mold"
        ))
    {
    }

    FMoldDomain::FMoldDomain(
        const FMoldDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        MoldModelName(From.MoldModelName),
        ParentKey(From.ParentKey)
    {

    }

    FMoldDomain::FGetTask::FGetTask(
        const TSharedPtr<FMoldDomain>& Self,
        const Request::FGetMoldByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FMoldDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FMoldDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Formation::Model::FMold>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithMoldModelName(Self->MoldModelName);
        const auto Future = Self->Client->GetMoldByUserId(
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
        Gs2::Formation::Model::Cache::FMoldCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            (ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>()),
            Request->GetMoldModelName(),
            TOptional<int32>(),
            ResultModel->GetItem()
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
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FMoldDomain::FGetTask>> FMoldDomain::Get(
        Request::FGetMoldByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FMoldDomain::FSetCapacityTask::FSetCapacityTask(
        const TSharedPtr<FMoldDomain>& Self,
        const Request::FSetMoldCapacityByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FMoldDomain::FSetCapacityTask::FSetCapacityTask(
        const FSetCapacityTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FMoldDomain::FSetCapacityTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Formation::Domain::Model::FMoldDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithMoldModelName(Self->MoldModelName);
        const auto Future = Self->Client->SetMoldCapacityByUserId(
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
        Gs2::Formation::Model::Cache::FMoldCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            (ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>()),
            Request->GetMoldModelName(),
            TOptional<int32>(),
            ResultModel->GetItem()
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
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FMoldDomain::FSetCapacityTask>> FMoldDomain::SetCapacity(
        Request::FSetMoldCapacityByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FSetCapacityTask>>(this->AsShared(), Request);
    }

    FMoldDomain::FAddCapacityTask::FAddCapacityTask(
        const TSharedPtr<FMoldDomain>& Self,
        const Request::FAddMoldCapacityByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FMoldDomain::FAddCapacityTask::FAddCapacityTask(
        const FAddCapacityTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FMoldDomain::FAddCapacityTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Formation::Domain::Model::FMoldDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithMoldModelName(Self->MoldModelName);
        const auto Future = Self->Client->AddMoldCapacityByUserId(
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
        Gs2::Formation::Model::Cache::FMoldCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            (ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>()),
            Request->GetMoldModelName(),
            TOptional<int32>(),
            ResultModel->GetItem()
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
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FMoldDomain::FAddCapacityTask>> FMoldDomain::AddCapacity(
        Request::FAddMoldCapacityByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FAddCapacityTask>>(this->AsShared(), Request);
    }

    FMoldDomain::FSubCapacityTask::FSubCapacityTask(
        const TSharedPtr<FMoldDomain>& Self,
        const Request::FSubMoldCapacityByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FMoldDomain::FSubCapacityTask::FSubCapacityTask(
        const FSubCapacityTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FMoldDomain::FSubCapacityTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Formation::Domain::Model::FMoldDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithMoldModelName(Self->MoldModelName);
        const auto Future = Self->Client->SubMoldCapacityByUserId(
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
        Gs2::Formation::Model::Cache::FMoldCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            (ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>()),
            Request->GetMoldModelName(),
            TOptional<int32>(),
            ResultModel->GetItem()
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
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FMoldDomain::FSubCapacityTask>> FMoldDomain::SubCapacity(
        Request::FSubMoldCapacityByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FSubCapacityTask>>(this->AsShared(), Request);
    }

    FMoldDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FMoldDomain>& Self,
        const Request::FDeleteMoldByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FMoldDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FMoldDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Formation::Domain::Model::FMoldDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithMoldModelName(Self->MoldModelName);
        const auto Future = Self->Client->DeleteMoldByUserId(
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

              if (!ResultModel.IsValid() || !((ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>())).IsSet())
                  {
                    const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                      Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("userId"), TEXT("userId is invalid."), TEXT("invalid_response")));
                      return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
                    }
              Gs2::Formation::Model::Cache::FMoldCache::Delete(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            (ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>()),
            Request->GetMoldModelName(),
            TOptional<int32>()
        );
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FMoldDomain::FDeleteTask>> FMoldDomain::Delete(
        Request::FDeleteMoldByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    Gs2::Formation::Domain::Iterator::FDescribeFormsByUserIdIteratorPtr FMoldDomain::Forms(
        const TOptional<FString> TimeOffsetToken
    ) const
    {
        return MakeShared<Gs2::Formation::Domain::Iterator::FDescribeFormsByUserIdIterator>(
            Gs2,
            Client,
            NamespaceName,
            MoldModelName,
            UserId,
            TimeOffsetToken
        );
    }

    Gs2::Core::Domain::CallbackID FMoldDomain::SubscribeForms(
    TFunction<void()> Callback

    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Formation::Model::FForm::TypeName,
            Gs2::Formation::Model::Cache::FFormCache::CreateCacheParentKey(
                NamespaceName,
                UserId,
                MoldModelName,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FMoldDomain::UnsubscribeForms(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Formation::Model::FForm::TypeName,
            Gs2::Formation::Model::Cache::FFormCache::CreateCacheParentKey(
                NamespaceName,
                UserId,
                MoldModelName,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FMoldDomain::FCollectFormsTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Formation::Model::FFormPtr>>, public TSharedFromThis<FCollectFormsTask>
    {
        const TSharedPtr<FMoldDomain> Self;
        const TFunction<void(TArray<Gs2::Formation::Model::FFormPtr>)> OnCollected;
    const TOptional<FString> QueryTimeOffsetToken;
    public:
        explicit FCollectFormsTask(const TSharedPtr<FMoldDomain>& Self, TFunction<void(TArray<Gs2::Formation::Model::FFormPtr>)> OnCollected,const TOptional<FString> TimeOffsetToken) : Self(Self), OnCollected(OnCollected), QueryTimeOffsetToken(TimeOffsetToken) {}
        FCollectFormsTask(const FCollectFormsTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Formation::Model::FFormPtr>>> Result) override
        {
            TArray<Gs2::Formation::Model::FFormPtr> Items;
            auto Iterator = Self->Forms(QueryTimeOffsetToken)->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Formation::Model::FFormPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FMoldDomain::SubscribeForms(
        TFunction<void(TArray<Gs2::Formation::Model::FFormPtr>)> Callback,const TOptional<FString> TimeOffsetToken
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Formation::Domain::FGs2FormationDomain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryUserId = UserId;
        const auto QueryMoldModelName = MoldModelName;
        const auto QueryTimeOffsetToken = TimeOffsetToken;
        const auto Parent = Gs2::Formation::Model::Cache::FFormCache::CreateCacheParentKey(
        NamespaceName,
        UserId,
        MoldModelName,
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Formation::Model::FForm::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Formation::Model::FFormPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Formation::Model::FForm>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryUserId, QueryMoldModelName, QueryTimeOffsetToken]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FMoldDomain>(Owner, WeakService.Pin(), QueryNamespaceName, QueryUserId, QueryMoldModelName);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectFormsTask>>(Domain, Callback, QueryTimeOffsetToken);
                Task->StartBackgroundTask();
            }
        );
    }

    void FMoldDomain::InvalidateForms(const TOptional<FString> TimeOffsetToken)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Formation::Model::FForm::TypeName,
            Gs2::Formation::Model::Cache::FFormCache::CreateCacheParentKey(
        NamespaceName,
        UserId,
        MoldModelName,
        TOptional<int32>()
    )
        );
    }

    FMoldDomain::FSubscribeFormsWithInitialCallTask::FSubscribeFormsWithInitialCallTask(const TSharedPtr<FMoldDomain>& Self, TFunction<void(TArray<Gs2::Formation::Model::FFormPtr>)> Callback,const TOptional<FString> TimeOffsetToken) : Self(Self), Callback(Callback), QueryTimeOffsetToken(TimeOffsetToken) {}
    FMoldDomain::FSubscribeFormsWithInitialCallTask::FSubscribeFormsWithInitialCallTask(const FSubscribeFormsWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
    Gs2::Core::Model::FGs2ErrorPtr FMoldDomain::FSubscribeFormsWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectFormsTask>>(Self, TFunction<void(TArray<Gs2::Formation::Model::FFormPtr>)>(), QueryTimeOffsetToken);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeForms(Callback, QueryTimeOffsetToken);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FMoldDomain::FSubscribeFormsWithInitialCallTask>> FMoldDomain::SubscribeFormsWithInitialCall(TFunction<void(TArray<Gs2::Formation::Model::FFormPtr>)> Callback,const TOptional<FString> TimeOffsetToken)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeFormsWithInitialCallTask>>(this->AsShared(), Callback, TimeOffsetToken);
    }

    TSharedPtr<Gs2::Formation::Domain::Model::FFormDomain> FMoldDomain::Form(
        const int32 Index
    )
    {
        return MakeShared<Gs2::Formation::Domain::Model::FFormDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId,
            MoldModelName,
            Index
        );
    }

    FString FMoldDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> MoldModelName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (MoldModelName.IsSet() ? *MoldModelName : "null") + ":" +
            ChildType;
    }

    FString FMoldDomain::CreateCacheKey(
        TOptional<FString> MoldModelName
    )
    {
        return FString("") +
            (MoldModelName.IsSet() ? *MoldModelName : "null");
    }

    FMoldDomain::FModelTask::FModelTask(
        const TSharedPtr<FMoldDomain> Self
    ): Self(Self)
    {

    }

    FMoldDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FMoldDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Formation::Model::FMold>> Result
    )
    {
        const auto CacheParentKey = Gs2::Formation::Model::Cache::FMoldCache::CreateCacheParentKey(

            Self->NamespaceName,
            Self->UserId,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::Formation::Model::Cache::FMoldCache::CreateCacheKey(

            Self->MoldModelName
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Formation::Model::FMold::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Formation::Model::FMoldPtr Value;
                const auto CacheHit = Gs2::Formation::Model::Cache::FMoldCache::TryGet(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->UserId,
                    Self->MoldModelName,
                    TOptional<int32>(),
                    &Value
                );
                if (CacheHit)
                {
                    *Result = Value;
                    return nullptr;
                }
                const auto Error = Gs2::Formation::Model::Cache::FMoldCache::Fetch(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->UserId,
                    Self->MoldModelName,
                    TOptional<int32>(),
                    [Self](Gs2::Formation::Model::FMoldPtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::Formation::Request::FGetMoldByUserIdRequest>()
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

    TSharedPtr<FAsyncTask<FMoldDomain::FModelTask>> FMoldDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FMoldDomain::FModelTask>>(this->AsShared());
    }

    void FMoldDomain::Invalidate()
    {
        Gs2::Formation::Model::Cache::FMoldCache::Delete(
            Gs2->Cache,

            NamespaceName,
            UserId,
            MoldModelName,
            TOptional<int32>()
        );
    }

    FMoldDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FMoldDomain>& Self,
        TFunction<void(Gs2::Formation::Model::FMoldPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FMoldDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FMoldDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FMoldDomain::FSubscribeWithInitialCallTask>> FMoldDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Formation::Model::FMoldPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FMoldDomain::Subscribe(
        TFunction<void(Gs2::Formation::Model::FMoldPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Formation::Model::Cache::FMoldCache::CreateCacheParentKey(

            NamespaceName,
            UserId,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Formation::Model::Cache::FMoldCache::CreateCacheKey(

            MoldModelName
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Formation::Domain::FGs2FormationDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryUserId = UserId;
        const TOptional<FString> QueryMoldModelName = MoldModelName;
        return Gs2->Cache->Subscribe(
            Gs2::Formation::Model::FMold::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Formation::Model::FMold>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryUserId, QueryMoldModelName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FMoldDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    QueryUserId,
                    QueryMoldModelName
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FMoldDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Formation::Model::Cache::FMoldCache::CreateCacheParentKey(

            NamespaceName,
            UserId,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Formation::Model::Cache::FMoldCache::CreateCacheKey(

            MoldModelName
        );
        Gs2->Cache->Unsubscribe(
            Gs2::Formation::Model::FMold::TypeName,
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
