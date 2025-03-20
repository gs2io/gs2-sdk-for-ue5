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

#include "Account/Domain/Model/TakeOverTypeModel.h"
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

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Account::Domain::Model
{

    FTakeOverTypeModelDomain::FTakeOverTypeModelDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Account::Domain::FGs2AccountDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<int32> Type
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Account::FGs2AccountRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        Type(Type),
        ParentKey(Gs2::Account::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "TakeOverTypeModel"
        ))
    {
    }

    FTakeOverTypeModelDomain::FTakeOverTypeModelDomain(
        const FTakeOverTypeModelDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        Type(From.Type),
        ParentKey(From.ParentKey)
    {

    }

    FTakeOverTypeModelDomain::FGetTask::FGetTask(
        const TSharedPtr<FTakeOverTypeModelDomain>& Self,
        const Request::FGetTakeOverTypeModelRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FTakeOverTypeModelDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FTakeOverTypeModelDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Account::Model::FTakeOverTypeModel>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithType(Self->Type);
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FTakeOverTypeModelDomain::FGetTask>> FTakeOverTypeModelDomain::Get(
        Request::FGetTakeOverTypeModelRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FTakeOverTypeModelDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> Type,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (Type.IsSet() ? *Type : "null") + ":" +
            ChildType;
    }

    FString FTakeOverTypeModelDomain::CreateCacheKey(
        TOptional<FString> Type
    )
    {
        return FString("") +
            (Type.IsSet() ? *Type : "null");
    }

    FTakeOverTypeModelDomain::FModelTask::FModelTask(
        const TSharedPtr<FTakeOverTypeModelDomain> Self
    ): Self(Self)
    {

    }

    FTakeOverTypeModelDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FTakeOverTypeModelDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Account::Model::FTakeOverTypeModel>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Account::Model::FTakeOverTypeModel> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Account::Model::FTakeOverTypeModel>(
            Self->ParentKey,
            Gs2::Account::Domain::Model::FTakeOverTypeModelDomain::CreateCacheKey(
                Self->Type.IsSet() ? FString::FromInt(*Self->Type) : TOptional<FString>()
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Account::Request::FGetTakeOverTypeModelRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Account::Domain::Model::FTakeOverTypeModelDomain::CreateCacheKey(
                    Self->Type.IsSet() ? FString::FromInt(*Self->Type) : TOptional<FString>()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Account::Model::FTakeOverTypeModel::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "takeOverTypeModel")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Account::Model::FTakeOverTypeModel>(
                Self->ParentKey,
                Gs2::Account::Domain::Model::FTakeOverTypeModelDomain::CreateCacheKey(
                    Self->Type.IsSet() ? FString::FromInt(*Self->Type) : TOptional<FString>()
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FTakeOverTypeModelDomain::FModelTask>> FTakeOverTypeModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FTakeOverTypeModelDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FTakeOverTypeModelDomain::Subscribe(
        TFunction<void(Gs2::Account::Model::FTakeOverTypeModelPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Account::Model::FTakeOverTypeModel::TypeName,
            ParentKey,
            Gs2::Account::Domain::Model::FTakeOverTypeModelDomain::CreateCacheKey(
                Type.IsSet() ? FString::FromInt(*Type) : TOptional<FString>()
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Account::Model::FTakeOverTypeModel>(obj));
            }
        );
    }

    void FTakeOverTypeModelDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Account::Model::FTakeOverTypeModel::TypeName,
            ParentKey,
            Gs2::Account::Domain::Model::FTakeOverTypeModelDomain::CreateCacheKey(
                Type.IsSet() ? FString::FromInt(*Type) : TOptional<FString>()
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

