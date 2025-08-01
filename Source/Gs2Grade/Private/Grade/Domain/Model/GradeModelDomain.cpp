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

#include "Grade/Domain/Model/GradeModel.h"
#include "Grade/Domain/Model/Namespace.h"
#include "Grade/Domain/Model/GradeModelMaster.h"
#include "Grade/Domain/Model/GradeModel.h"
#include "Grade/Domain/Model/User.h"
#include "Grade/Domain/Model/UserAccessToken.h"
#include "Grade/Domain/Model/Status.h"
#include "Grade/Domain/Model/StatusAccessToken.h"
#include "Grade/Domain/Model/CurrentGradeMaster.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Grade::Domain::Model
{

    FGradeModelDomain::FGradeModelDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Grade::Domain::FGs2GradeDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> GradeName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Grade::FGs2GradeRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        GradeName(GradeName),
        ParentKey(Gs2::Grade::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "GradeModel"
        ))
    {
    }

    FGradeModelDomain::FGradeModelDomain(
        const FGradeModelDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        GradeName(From.GradeName),
        ParentKey(From.ParentKey)
    {

    }

    FGradeModelDomain::FGetTask::FGetTask(
        const TSharedPtr<FGradeModelDomain>& Self,
        const Request::FGetGradeModelRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGradeModelDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGradeModelDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Grade::Model::FGradeModel>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithGradeName(Self->GradeName);
        const auto Future = Self->Client->GetGradeModel(
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

    TSharedPtr<FAsyncTask<FGradeModelDomain::FGetTask>> FGradeModelDomain::Get(
        Request::FGetGradeModelRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FGradeModelDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> GradeName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (GradeName.IsSet() ? *GradeName : "null") + ":" +
            ChildType;
    }

    FString FGradeModelDomain::CreateCacheKey(
        TOptional<FString> GradeName
    )
    {
        return FString("") +
            (GradeName.IsSet() ? *GradeName : "null");
    }

    FGradeModelDomain::FModelTask::FModelTask(
        const TSharedPtr<FGradeModelDomain> Self
    ): Self(Self)
    {

    }

    FGradeModelDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FGradeModelDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Grade::Model::FGradeModel>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Grade::Model::FGradeModel> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Grade::Model::FGradeModel>(
            Self->ParentKey,
            Gs2::Grade::Domain::Model::FGradeModelDomain::CreateCacheKey(
                Self->GradeName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Grade::Request::FGetGradeModelRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Grade::Domain::Model::FGradeModelDomain::CreateCacheKey(
                    Self->GradeName
                );
                Self->Gs2->Cache->Put(
                    Gs2::Grade::Model::FGradeModel::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "gradeModel")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Grade::Model::FGradeModel>(
                Self->ParentKey,
                Gs2::Grade::Domain::Model::FGradeModelDomain::CreateCacheKey(
                    Self->GradeName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGradeModelDomain::FModelTask>> FGradeModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FGradeModelDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FGradeModelDomain::Subscribe(
        TFunction<void(Gs2::Grade::Model::FGradeModelPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Grade::Model::FGradeModel::TypeName,
            ParentKey,
            Gs2::Grade::Domain::Model::FGradeModelDomain::CreateCacheKey(
                GradeName
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Grade::Model::FGradeModel>(obj));
            }
        );
    }

    void FGradeModelDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Grade::Model::FGradeModel::TypeName,
            ParentKey,
            Gs2::Grade::Domain::Model::FGradeModelDomain::CreateCacheKey(
                GradeName
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

