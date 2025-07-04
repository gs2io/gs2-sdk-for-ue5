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
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithStaminaName(Self->StaminaName)
            ->WithAccessToken(Self->AccessToken->GetToken());
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
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithStaminaName(Self->StaminaName)
            ->WithAccessToken(Self->AccessToken->GetToken());
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
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithStaminaName(Self->StaminaName)
            ->WithAccessToken(Self->AccessToken->GetToken());
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
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithStaminaName(Self->StaminaName)
            ->WithAccessToken(Self->AccessToken->GetToken());
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
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithStaminaName(Self->StaminaName)
            ->WithAccessToken(Self->AccessToken->GetToken());
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
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithStaminaName(Self->StaminaName)
            ->WithAccessToken(Self->AccessToken->GetToken());
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
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithStaminaName(Self->StaminaName)
            ->WithAccessToken(Self->AccessToken->GetToken());
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
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithStaminaName(Self->StaminaName);
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
        const auto Domain = Self;
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
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithStaminaName(Self->StaminaName);
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
        const auto Domain = Self;
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
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithStaminaName(Self->StaminaName);
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
        const auto Domain = Self;
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
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithStaminaName(Self->StaminaName);
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
        const auto Domain = Self;
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
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithStaminaName(Self->StaminaName);
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
        const auto Domain = Self;
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
                MakeShared<Gs2::Stamina::Request::FGetStaminaRequest>()
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

    TSharedPtr<FAsyncTask<FStaminaAccessTokenDomain::FModelTask>> FStaminaAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FStaminaAccessTokenDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FStaminaAccessTokenDomain::Subscribe(
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

    void FStaminaAccessTokenDomain::Unsubscribe(
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

