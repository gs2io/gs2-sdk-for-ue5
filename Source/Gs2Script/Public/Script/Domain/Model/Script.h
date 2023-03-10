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

// ReSharper disable CppUnusedIncludeDirective

#pragma once

#include "Core/Domain/Gs2Core.h"
#include "Auth/Gs2Auth.h"
#include "Script/Gs2Script.h"
#include "Script/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Script/Domain/Iterator/DescribeScriptsIterator.h"

namespace Gs2::Script::Domain::Model
{
    class FNamespaceDomain;
    class FScriptDomain;

    class GS2SCRIPT_API FScriptDomain:
        public TSharedFromThis<FScriptDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Script::FGs2ScriptRestClientPtr Client;

        public:
        TOptional<int32> Code;
        TOptional<FString> Result;
        TOptional<int32> ExecuteTime;
        TOptional<int32> Charged;
        TSharedPtr<TArray<FString>> Output;
        TOptional<int32> GetCode() const
        {
            return Code;
        }
        TOptional<FString> GetResult() const
        {
            return Result;
        }
        TOptional<int32> GetExecuteTime() const
        {
            return ExecuteTime;
        }
        TOptional<int32> GetCharged() const
        {
            return Charged;
        }
        TSharedPtr<TArray<FString>> GetOutput() const
        {
            return Output;
        }
        TOptional<FString> NamespaceName;
        TOptional<FString> ScriptName;
    private:

        FString ParentKey;

    public:

        FScriptDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> ScriptName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FScriptDomain(
            const FScriptDomain& From
        );

        class GS2SCRIPT_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Script::Model::FScript>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FScriptDomain> Self;
            const Request::FGetScriptRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FScriptDomain> Self,
                const Request::FGetScriptRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Script::Model::FScript>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetScriptRequestPtr Request
        );

        class GS2SCRIPT_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Script::Domain::Model::FScriptDomain>,
            public TSharedFromThis<FUpdateTask>
        {
            const TSharedPtr<FScriptDomain> Self;
            const Request::FUpdateScriptRequestPtr Request;
        public:
            explicit FUpdateTask(
                const TSharedPtr<FScriptDomain> Self,
                const Request::FUpdateScriptRequestPtr Request
            );

            FUpdateTask(
                const FUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Script::Domain::Model::FScriptDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateScriptRequestPtr Request
        );

        class GS2SCRIPT_API FUpdateFromGitHubTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Script::Domain::Model::FScriptDomain>,
            public TSharedFromThis<FUpdateFromGitHubTask>
        {
            const TSharedPtr<FScriptDomain> Self;
            const Request::FUpdateScriptFromGitHubRequestPtr Request;
        public:
            explicit FUpdateFromGitHubTask(
                const TSharedPtr<FScriptDomain> Self,
                const Request::FUpdateScriptFromGitHubRequestPtr Request
            );

            FUpdateFromGitHubTask(
                const FUpdateFromGitHubTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Script::Domain::Model::FScriptDomain>> Result
            ) override;
        };
        friend FUpdateFromGitHubTask;

        TSharedPtr<FAsyncTask<FUpdateFromGitHubTask>> UpdateFromGitHub(
            Request::FUpdateScriptFromGitHubRequestPtr Request
        );

        class GS2SCRIPT_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Script::Domain::Model::FScriptDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FScriptDomain> Self;
            const Request::FDeleteScriptRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FScriptDomain> Self,
                const Request::FDeleteScriptRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Script::Domain::Model::FScriptDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteScriptRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> ScriptName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> ScriptName
        );

        class GS2SCRIPT_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Script::Model::FScript>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FScriptDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FScriptDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Script::Model::FScript>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };

    typedef TSharedPtr<FScriptDomain> FScriptDomainPtr;
}
