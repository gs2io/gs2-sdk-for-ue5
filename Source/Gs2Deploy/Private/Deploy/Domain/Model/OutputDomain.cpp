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

#include "Deploy/Domain/Model/Output.h"
#include "Deploy/Domain/Model/Stack.h"
#include "Deploy/Domain/Model/Resource.h"
#include "Deploy/Domain/Model/Event.h"
#include "Deploy/Domain/Model/Output.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Deploy::Domain::Model
{

    FOutputDomain::FOutputDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Deploy::Domain::FGs2DeployDomainPtr& Service,
        const TOptional<FString> StackName,
        const TOptional<FString> OutputName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Deploy::FGs2DeployRestClient>(Gs2->RestSession)),
        StackName(StackName),
        OutputName(OutputName),
        ParentKey(Gs2::Deploy::Domain::Model::FStackDomain::CreateCacheParentKey(
            StackName,
            "Output"
        ))
    {
    }

    FOutputDomain::FOutputDomain(
        const FOutputDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        StackName(From.StackName),
        OutputName(From.OutputName),
        ParentKey(From.ParentKey)
    {

    }

    FOutputDomain::FGetTask::FGetTask(
        const TSharedPtr<FOutputDomain>& Self,
        const Request::FGetOutputRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FOutputDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FOutputDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Deploy::Model::FOutput>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithStackName(Self->StackName)
            ->WithOutputName(Self->OutputName);
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FOutputDomain::FGetTask>> FOutputDomain::Get(
        Request::FGetOutputRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FOutputDomain::CreateCacheParentKey(
        TOptional<FString> StackName,
        TOptional<FString> OutputName,
        FString ChildType
    )
    {
        return FString("") +
            (StackName.IsSet() ? *StackName : "null") + ":" +
            (OutputName.IsSet() ? *OutputName : "null") + ":" +
            ChildType;
    }

    FString FOutputDomain::CreateCacheKey(
        TOptional<FString> OutputName
    )
    {
        return FString("") +
            (OutputName.IsSet() ? *OutputName : "null");
    }

    FOutputDomain::FModelTask::FModelTask(
        const TSharedPtr<FOutputDomain> Self
    ): Self(Self)
    {

    }

    FOutputDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FOutputDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Deploy::Model::FOutput>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Deploy::Model::FOutput> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Deploy::Model::FOutput>(
            Self->ParentKey,
            Gs2::Deploy::Domain::Model::FOutputDomain::CreateCacheKey(
                Self->OutputName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Deploy::Request::FGetOutputRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Deploy::Domain::Model::FOutputDomain::CreateCacheKey(
                    Self->OutputName
                );
                Self->Gs2->Cache->Put(
                    Gs2::Deploy::Model::FOutput::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "output")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::Deploy::Model::FOutput>(
                Self->ParentKey,
                Gs2::Deploy::Domain::Model::FOutputDomain::CreateCacheKey(
                    Self->OutputName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FOutputDomain::FModelTask>> FOutputDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FOutputDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FOutputDomain::Subscribe(
        TFunction<void(Gs2::Deploy::Model::FOutputPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::Deploy::Model::FOutput::TypeName,
            ParentKey,
            Gs2::Deploy::Domain::Model::FOutputDomain::CreateCacheKey(
                OutputName
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Deploy::Model::FOutput>(obj));
            }
        );
    }

    void FOutputDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Deploy::Model::FOutput::TypeName,
            ParentKey,
            Gs2::Deploy::Domain::Model::FOutputDomain::CreateCacheKey(
                OutputName
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

