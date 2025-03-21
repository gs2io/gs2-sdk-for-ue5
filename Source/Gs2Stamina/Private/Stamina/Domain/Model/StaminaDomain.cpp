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

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Stamina::Domain::Model
{

    FStaminaDomain::FStaminaDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Stamina::Domain::FGs2StaminaDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<FString> StaminaName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Stamina::FGs2StaminaRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        StaminaName(StaminaName),
        ParentKey(Gs2::Stamina::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId,
            "Stamina"
        ))
    {
    }

    FStaminaDomain::FStaminaDomain(
        const FStaminaDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        StaminaName(From.StaminaName),
        ParentKey(From.ParentKey)
    {

    }

    FStaminaDomain::FGetTask::FGetTask(
        const TSharedPtr<FStaminaDomain>& Self,
        const Request::FGetStaminaByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStaminaDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStaminaDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Stamina::Model::FStamina>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithStaminaName(Self->StaminaName)
            ->WithUserId(Self->UserId);
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStaminaDomain::FGetTask>> FStaminaDomain::Get(
        Request::FGetStaminaByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FStaminaDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FStaminaDomain>& Self,
        const Request::FUpdateStaminaByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStaminaDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStaminaDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FStaminaDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithStaminaName(Self->StaminaName)
            ->WithUserId(Self->UserId);
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStaminaDomain::FUpdateTask>> FStaminaDomain::Update(
        Request::FUpdateStaminaByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FStaminaDomain::FConsumeTask::FConsumeTask(
        const TSharedPtr<FStaminaDomain>& Self,
        const Request::FConsumeStaminaByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStaminaDomain::FConsumeTask::FConsumeTask(
        const FConsumeTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStaminaDomain::FConsumeTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FStaminaDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithStaminaName(Self->StaminaName)
            ->WithUserId(Self->UserId);
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStaminaDomain::FConsumeTask>> FStaminaDomain::Consume(
        Request::FConsumeStaminaByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FConsumeTask>>(this->AsShared(), Request);
    }

    FStaminaDomain::FApplyTask::FApplyTask(
        const TSharedPtr<FStaminaDomain>& Self,
        const Request::FApplyStaminaByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStaminaDomain::FApplyTask::FApplyTask(
        const FApplyTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStaminaDomain::FApplyTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FStaminaDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithStaminaName(Self->StaminaName)
            ->WithUserId(Self->UserId);
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStaminaDomain::FApplyTask>> FStaminaDomain::Apply(
        Request::FApplyStaminaByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FApplyTask>>(this->AsShared(), Request);
    }

    FStaminaDomain::FRecoverTask::FRecoverTask(
        const TSharedPtr<FStaminaDomain>& Self,
        const Request::FRecoverStaminaByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStaminaDomain::FRecoverTask::FRecoverTask(
        const FRecoverTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStaminaDomain::FRecoverTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FStaminaDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithStaminaName(Self->StaminaName)
            ->WithUserId(Self->UserId);
        auto Domain = Self;
        if (ResultModel != nullptr)
        {
            Domain->OverflowValue = *ResultModel->GetOverflowValue();
        }

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStaminaDomain::FRecoverTask>> FStaminaDomain::Recover(
        Request::FRecoverStaminaByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FRecoverTask>>(this->AsShared(), Request);
    }

    FStaminaDomain::FRaiseMaxValueTask::FRaiseMaxValueTask(
        const TSharedPtr<FStaminaDomain>& Self,
        const Request::FRaiseMaxValueByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStaminaDomain::FRaiseMaxValueTask::FRaiseMaxValueTask(
        const FRaiseMaxValueTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStaminaDomain::FRaiseMaxValueTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FStaminaDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithStaminaName(Self->StaminaName)
            ->WithUserId(Self->UserId);
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStaminaDomain::FRaiseMaxValueTask>> FStaminaDomain::RaiseMaxValue(
        Request::FRaiseMaxValueByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FRaiseMaxValueTask>>(this->AsShared(), Request);
    }

    FStaminaDomain::FDecreaseMaxValueTask::FDecreaseMaxValueTask(
        const TSharedPtr<FStaminaDomain>& Self,
        const Request::FDecreaseMaxValueByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStaminaDomain::FDecreaseMaxValueTask::FDecreaseMaxValueTask(
        const FDecreaseMaxValueTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStaminaDomain::FDecreaseMaxValueTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FStaminaDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithStaminaName(Self->StaminaName)
            ->WithUserId(Self->UserId);
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStaminaDomain::FDecreaseMaxValueTask>> FStaminaDomain::DecreaseMaxValue(
        Request::FDecreaseMaxValueByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDecreaseMaxValueTask>>(this->AsShared(), Request);
    }

    FStaminaDomain::FSetMaxValueTask::FSetMaxValueTask(
        const TSharedPtr<FStaminaDomain>& Self,
        const Request::FSetMaxValueByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStaminaDomain::FSetMaxValueTask::FSetMaxValueTask(
        const FSetMaxValueTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStaminaDomain::FSetMaxValueTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FStaminaDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithStaminaName(Self->StaminaName)
            ->WithUserId(Self->UserId);
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStaminaDomain::FSetMaxValueTask>> FStaminaDomain::SetMaxValue(
        Request::FSetMaxValueByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FSetMaxValueTask>>(this->AsShared(), Request);
    }

    FStaminaDomain::FSetRecoverIntervalTask::FSetRecoverIntervalTask(
        const TSharedPtr<FStaminaDomain>& Self,
        const Request::FSetRecoverIntervalByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStaminaDomain::FSetRecoverIntervalTask::FSetRecoverIntervalTask(
        const FSetRecoverIntervalTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStaminaDomain::FSetRecoverIntervalTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FStaminaDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithStaminaName(Self->StaminaName)
            ->WithUserId(Self->UserId);
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStaminaDomain::FSetRecoverIntervalTask>> FStaminaDomain::SetRecoverInterval(
        Request::FSetRecoverIntervalByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FSetRecoverIntervalTask>>(this->AsShared(), Request);
    }

    FStaminaDomain::FSetRecoverValueTask::FSetRecoverValueTask(
        const TSharedPtr<FStaminaDomain>& Self,
        const Request::FSetRecoverValueByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStaminaDomain::FSetRecoverValueTask::FSetRecoverValueTask(
        const FSetRecoverValueTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStaminaDomain::FSetRecoverValueTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FStaminaDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithStaminaName(Self->StaminaName)
            ->WithUserId(Self->UserId);
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStaminaDomain::FSetRecoverValueTask>> FStaminaDomain::SetRecoverValue(
        Request::FSetRecoverValueByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FSetRecoverValueTask>>(this->AsShared(), Request);
    }

    FStaminaDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FStaminaDomain>& Self,
        const Request::FDeleteStaminaByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStaminaDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStaminaDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FStaminaDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithStaminaName(Self->StaminaName)
            ->WithUserId(Self->UserId);
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStaminaDomain::FDeleteTask>> FStaminaDomain::Delete(
        Request::FDeleteStaminaByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FStaminaDomain::CreateCacheParentKey(
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

    FString FStaminaDomain::CreateCacheKey(
        TOptional<FString> StaminaName
    )
    {
        return FString("") +
            (StaminaName.IsSet() ? *StaminaName : "null");
    }

    FStaminaDomain::FModelTask::FModelTask(
        const TSharedPtr<FStaminaDomain> Self
    ): Self(Self)
    {

    }

    FStaminaDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FStaminaDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Stamina::Model::FStamina>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Stamina::Model::FStamina> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Stamina::Model::FStamina>(
            Self->ParentKey,
            Gs2::Stamina::Domain::Model::FStaminaDomain::CreateCacheKey(
                Self->StaminaName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Stamina::Request::FGetStaminaByUserIdRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Stamina::Domain::Model::FStaminaDomain::CreateCacheKey(
                    Self->StaminaName
                );
                Self->Gs2->Cache->Put(
                    Gs2::Stamina::Model::FStamina::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "stamina")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Stamina::Model::FStamina>(
                Self->ParentKey,
                Gs2::Stamina::Domain::Model::FStaminaDomain::CreateCacheKey(
                    Self->StaminaName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStaminaDomain::FModelTask>> FStaminaDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FStaminaDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FStaminaDomain::Subscribe(
        TFunction<void(Gs2::Stamina::Model::FStaminaPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Stamina::Model::FStamina::TypeName,
            ParentKey,
            Gs2::Stamina::Domain::Model::FStaminaDomain::CreateCacheKey(
                StaminaName
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Stamina::Model::FStamina>(obj));
            }
        );
    }

    void FStaminaDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Stamina::Model::FStamina::TypeName,
            ParentKey,
            Gs2::Stamina::Domain::Model::FStaminaDomain::CreateCacheKey(
                StaminaName
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

